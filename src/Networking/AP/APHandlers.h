#pragma once
#include <WiFi.h>
#include <Utility/ArduinoJson.h>
#include <HTTPSServer.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <HTTPURLEncodedBodyParser.hpp>
#include "../HTML/APHTML.h"

using namespace httpsserver;

void handleNetworkLogin(HTTPRequest* req, HTTPResponse* res)
{
    if(req->getMethod()=="GET")
        res->println(change_network);
    else
    {
        HTTPURLEncodedBodyParser parser(req);
        std::string network, password;
        char buf[128];
        while(parser.nextField()){
            std::string field = parser.getFieldName();
            if(field=="networks")
            {
                size_t readLength = parser.read((byte*)buf, 128);
                network = std::string(buf, readLength);
            }
            else if(field=="password")
            {
                size_t readLength = parser.read((byte*)buf, 128);
                password = std::string(buf, readLength);
            }
            else
            {
                res->println("Unexpected field");
                Logger::Error("Network Login", "Unexpected field in POST request");
                return;
            }
        }

        WiFi.disconnect();
        WiFi.begin(network.c_str(), password.c_str());
        delay(3000);
        if(WiFi.status()!=WL_CONNECTED)
        {
            StaticJsonDocument<64> doc;
            doc["success"]=false;
            
            String json;
            serializeJson(doc, json);
            res->setHeader("Content-Type", "application/json");
            res->println(json);

            Logger::Warning("Connection unsuccessful");
        }
        else
        {
            StaticJsonDocument<64> doc;
            doc["success"]=true;

            String url = "https://" + WiFi.localIP().toString();
            doc["url"] = url;

            String json;
            serializeJson(doc, json);
            res->setHeader("Content-Type", "application/json");
            res->println(json);

            Logger::Info("Connected to the network: " + String(network.c_str()));
        }
    }
}

void handleGetNetworks(HTTPRequest* req, HTTPResponse* res)
{
    if(req->getMethod()=="POST")
    {
        req->discardRequestBody();
        res->setStatusCode(405);
        res->setStatusText("POST is not allowed for this request");
        res->println("POST is forbidden for this request, try GET request");
        return;
    }

    DynamicJsonDocument json(1024);
    int network_count = WiFi.scanNetworks();
    json["length"] = network_count;
    for(int x =0;x<network_count;x++)
        json["values"][x] = WiFi.SSID(x);
    
    String serialized;
    serializeJson(json, serialized);

    res->setHeader("Content-Type", "application/json");
    res->println(serialized);
}