#pragma once
#include "IAPI.h"
#include "Utility/vector.h"
#include "Utility/Logger.h"
#include "Utility/ArduinoJson.h"
#include "Utility/sha256.h"
#include "Networking/Headers/Headers.h"
#include "Networking/Requests/RequestManager.h"
#include "StationInfo.h"
#include "DeviceDetail.h"
#include "DailyUsage.h"

using IDType = unsigned long long;

class SolarmanAPI : public IAPI
{
    private:
        const String tokenServer = "https://home.solarmanpv.com/mdc-eu/oauth-s/oauth/token";
        const String stationsIDServer = "https://globalhome.solarmanpv.com/maintain-s/operating/station/search?order.direction=DESC&order.property=id";//&page=1&size=1
        const String stationServer = "https://globalhome.solarmanpv.com/maintain-s/fast/system/";
        const String deviceDetail="https://globalhome.solarmanpv.com/device-s/device/detail/";
        const String dailyUsage ="https://globalhome.solarmanpv.com/maintain-s/history/power/analysis/"; //station id,payload:  {year,month,day}
        const char* ntpServer = "pool.ntp.org"; //for getting time
        const long gmtOffsetSec = 0;
        const int daylightOffsetSec = 3600;
    public:
        vector<IDType> GetUserStationsID();
        StationInfo getStationInfo(const int& id);
        DeviceDetail getDeviceDetail(const int& id, const int& deviceID);
        DailyUsage getStationDailyUsage(const int& id);

        bool RequestToken(const String& username, const String& password) override;
};

bool SolarmanAPI::RequestToken(const String& username, const String& password)
{
    RequestManager request;
    TypeJSONHeader json;
    AcceptJSONHeader acceptJson;
    StaticJsonDocument<512> payload;


    payload["grant_type"]="mdc_password";
    payload["username"] = username;
    payload["clear_text_pwd"] = password;
    payload["password"] = GenerateSHA256(password);
    payload["identity_type"] =2;
    payload["client_id"]="test";

    String payloadStr;
    serializeJson(payload, payloadStr);


    auto response = request.GetRequest(tokenServer,payloadStr, {json, acceptJson}, app::HTTPRequestType::POST);

    if(response.isError())
    {
        Logger::Error("Solarman API", "Code: "+String(response.ReturnCode()) + String("(")+response.GetResponse()+String(")"));
        return false;
    }

    StaticJsonDocument<32> filter;
    DynamicJsonDocument token(1024);
    filter["access_token"] = true;

    DeserializationError err = deserializeJson(token, response.GetResponse(), DeserializationOption::Filter(filter));
    if(err)
    {
            Logger::Error("Solarman API", "Deserialization of data failed (" + String(err.c_str()) +")");
            return false;
    }

    String tokenStr = token["access_token"];
    SetToken(tokenStr);

    return true;
}

/*
    this function calls solarman api, to get stations ids, request size is 1, more is not yet supported
    This function is optimized to use as little memory as possible, neverthless request still is loaded into memory (+-2.1 kb) per request
    ID in json document: (object)->["data"]->[index]->["id"]
    (object)->["total"] if you want to add support for more than 1 value per request
*/
vector<IDType> SolarmanAPI::GetUserStationsID()
{
    if(!isTokenSet())
    {
        Logger::Error("Solarman API", "Authorization token is not set");
        return vector<IDType>();
    }

    const int reuqestSize=1;
    int page=1;

    RequestManager request;
    String payload = "{}";
    BearerAuthHeader token=BearerAuthHeader(GetToken());
    TypeJSONHeader json;
    vector<IDType> out;
    
    StaticJsonDocument<128> doc; //128 is just enough
    StaticJsonDocument<64> filter; //create filter, to make size smaller
    filter["data"][0]["id"]=true;

    while(true) //breaks when error occurs, or when there is no data to parse
    {
        String requestQuery = stationsIDServer + "&page="+String(page)+"&size="+String(reuqestSize);
        auto response = request.GetRequest(requestQuery,payload,{token, json}, app::HTTPRequestType::POST);
        if(response.isError())
        {
            Logger::Error("Solarman API", "Code: "+String(response.ReturnCode()) + String("(")+response.GetResponse()+String(")"));
            return vector<IDType>();
        }

        DeserializationError err = deserializeJson(doc, response.GetResponse(), DeserializationOption::Filter(filter));

        if(err)
        {
            Logger::Error("Solarman API", "Deserialization of data failed (" + String(err.c_str()) +")");
            return vector<IDType>();
        }

        if(doc["data"].isNull() || doc["data"].size()==0)//if data is empty, there are no more records to get
            break;

        IDType ID = doc["data"][0]["id"].as<IDType>();

        out.push_back(ID);
        page++;
    }

    return out;
}

StationInfo SolarmanAPI::getStationInfo(const int& id)
{
    if(!isTokenSet())
    {
        Logger::Error("Solarman API", "Authorization token is not set");
        return StationInfo();
    }

    RequestManager request;
    String url = stationServer + String(id);
    BearerAuthHeader token=BearerAuthHeader(GetToken());

    StaticJsonDocument<512> doc;
    StaticJsonDocument<128> filter;

    filter["usePower"]=true; //Consumption
    filter["generationPower"]=true; //Production
    filter["chargePower"]=true; //battery charge
    filter["dischargePower"] = true; //battery discharge
    filter["batterySoc"]=true; //battery percent
    filter["wirePower"] = true; //power to grid (if is minus, then power is from grid, otherwise to grid)

    auto response = request.GetRequest(url, "",{token});

    if(response.isError())
    {
        Logger::Error("Solarman API", "Code: "+String(response.ReturnCode()) + String("(")+response.GetResponse()+String(")"));
        return StationInfo();
    }

    DeserializationError err = deserializeJson(doc, response.GetResponse(), DeserializationOption::Filter(filter));

    if(err)
    {
        Logger::Error("Solarman API", "Deserialization of data failed (" + String(err.c_str()) +")");
        return StationInfo();
    }

    return StationInfo {
        .Consumption = doc["usePower"],
        .Production=doc["generationPower"],
        .batteryCharge = doc["chargePower"].isNull() ? 0.0 : doc["chargePower"],
        .batteryDischarge = doc["dischargePower"].isNull() ? 0.0 : -doc["dischargePower"].as<double>(), //discharge is minus
        .fromGridPower = doc["wirePower"] < 0 ? -doc["wirePower"].as<double>() : 0.0,
        .toGridPower = doc["wirePower"] > 0 ? doc["wirePower"] : 0.0,
        .batteryPercent = doc["batterySoc"]
    };
}

DeviceDetail SolarmanAPI::getDeviceDetail(const int& id, const int& deviceID)
{
    if(!isTokenSet())
    {
        Logger::Error("Solarman API", "Authorization token is not set");
        return DeviceDetail();
    }

    RequestManager request;

    StaticJsonDocument<128> payloadJson;
    payloadJson["deviceId"] = deviceID;
    payloadJson["language"]="pl";
    payloadJson["needRealTimeDataFlag"]=true;
    payloadJson["siteId"]=id;

    String payload;
    BearerAuthHeader token=BearerAuthHeader(GetToken());
    TypeJSONHeader json;

    serializeJson(payloadJson, payload);

    DynamicJsonDocument doc(12000);
    StaticJsonDocument<128> filter;
    filter["paramCategoryList"][0]["fieldList"][0]["value"]=true;

    auto response = request.GetRequest(deviceDetail,payload,{token,json},app::HTTPRequestType::POST);
 
    if(response.isError())
    {
        Logger::Error("Solarman API", "Code: "+String(response.ReturnCode()) + String("(")+response.GetResponse()+String(")"));
        return DeviceDetail();
    }

    DeserializationError err = deserializeJson(doc, response.GetResponse(), DeserializationOption::Filter(filter));

    if(err)
    {
        Logger::Error("Solarman API", "Deserialization of data failed (" + String(err.c_str()) +")");
        return DeviceDetail();
    }

    DCInfo pv1, pv2;
    pv1.voltage=doc["paramCategoryList"][2]["fieldList"][0]["value"];     pv2.voltage=doc["paramCategoryList"][2]["fieldList"][1]["value"];
    pv1.current=doc["paramCategoryList"][2]["fieldList"][2]["value"];     pv2.current=doc["paramCategoryList"][2]["fieldList"][3]["value"];
    pv1.power=doc["paramCategoryList"][2]["fieldList"][4]["value"];       pv2.power=doc["paramCategoryList"][2]["fieldList"][5]["value"];

    ACInfo R,S,T;
    R.voltage = doc["paramCategoryList"][2]["fieldList"][6]["value"]; S.voltage=doc["paramCategoryList"][2]["fieldList"][7]["value"]; 
    T.voltage=doc["paramCategoryList"][2]["fieldList"][8]["value"]; R.current = doc["paramCategoryList"][2]["fieldList"][9]["value"]; 
    S.current=doc["paramCategoryList"][2]["fieldList"][10]["value"]; T.current=doc["paramCategoryList"][2]["fieldList"][11]["value"];

    double RFreq = doc["paramCategoryList"][2]["fieldList"][12]["value"];

    return DeviceDetail
    {
        .PV1 = pv1,
        .PV2 =pv2,
        .R=R,
        .S=S,
        .T=T,
        .RFrequency = RFreq
    };
}

DailyUsage SolarmanAPI::getStationDailyUsage(const int& id)
{
    if(!isTokenSet())
    {
        Logger::Error("Solarman API", "Authorization token is not set");
        return DailyUsage();
    }

    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);
    tm timeinfo;
    if(!getLocalTime(&timeinfo))
        return DailyUsage();

    RequestManager request;
    int year = timeinfo.tm_year + 1900;// year value is years since 1900
    int month = timeinfo.tm_mon + 1; //+1 , cause tm_mon is months since January
    int day = timeinfo.tm_mday;

    BearerAuthHeader token=BearerAuthHeader(GetToken());

    String dailyUsageLink = dailyUsage + String(id) + "/day?year="+String(year)+"&month="+String(month)+"&day="+String(day);

    StaticJsonDocument<256> doc;
    StaticJsonDocument<128> filter;
    filter["genValue"]=true;
    filter["useValue"]=true;
    filter["gvForGrid"]=true;
    filter["uvFromBuy"]=true; //use from grid

    auto response = request.GetRequest(dailyUsageLink,"",{token},app::HTTPRequestType::GET);
 
    if(response.isError())
    {
        Logger::Error("Solarman API", "Code: "+String(response.ReturnCode()) + String("(")+response.GetResponse()+String(")"));
        return DailyUsage();
    }

    DeserializationError err = deserializeJson(doc, response.GetResponse(), DeserializationOption::Filter(filter));

    if(err)
    {
        Logger::Error("Solarman API", "Deserialization of data failed (" + String(err.c_str()) +")");
        return DailyUsage();
    }

    //values are in kW, convert them to W
    return DailyUsage{
        .production = doc["genValue"].as<double>() *1000,
        .consumption = doc["useValue"].as<double>() * 1000,
        .gridIn = doc["gvForGrid"].as<double>() * 1000,
        .gridOut = doc["uvFromBuy"].as<double>() * 1000
    };
}