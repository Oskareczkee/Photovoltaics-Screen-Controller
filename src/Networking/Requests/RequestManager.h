#pragma once
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "ErrorRequest.h"
#include "Utility/vector.h"
#include "HTTPRequest.h"
#include "ErrorRequest.h"
#include "../Headers/HTTPHeader.h"
#include "cert.h"
#include "private_key.h"

class RequestManager
{
    public:
        RequestManager(){}
        app::HTTPRequest GetRequest(String website, 
                               String payload = String(),
                               vector<app::HTTPHeader>headers = vector<app::HTTPHeader>(), 
                               app::HTTPRequestType type = app::HTTPRequestType::GET);

        bool isRequestPossible(){return WiFi.status()==WL_CONNECTED;}
};
app::HTTPRequest RequestManager::GetRequest(String website, 
                                       String payload,
                                       vector<app::HTTPHeader>headers, 
                                       app::HTTPRequestType type)
{
    if(!isRequestPossible())
        return ErrorRequest("WiFi connection is not established","");
    else if(type==app::HTTPRequestType::NONE)
        return ErrorRequest("Invalid Request type","");

    WiFiClientSecure secureWiFi;
    secureWiFi.setInsecure();
    HTTPClient client;
    client.begin(secureWiFi, website);

    for(auto h : headers)
        client.addHeader(h.GetName(), h.GetValue());
        
    int response = type==app::HTTPRequestType::GET ? client.GET() : client.POST(payload);

    if(response > 299 || response < 200)
    {
        String clientResponse = client.getString();
        client.end();
        return ErrorRequest("Response was not successful, check code",clientResponse, response);
    }

    String clientResponse = client.getString();
    client.end();
    return app::HTTPRequest(type, clientResponse, response);
}