#pragma once
#include <WiFi.h>
#include <HTTPSServer.hpp>
#include <HTTPRequest.hpp>
#include <HTTPResponse.hpp>
#include <HTTPURLEncodedBodyParser.hpp>
#include "../HTML/STAHTML.h"
#include "Utility/Logger.h"
#include "Networking/NetworkManager.h"
#include "Networking/APIManager.h"

using namespace httpsserver;

void PrintStandardPOSTError(HTTPRequest* req, HTTPResponse* res)
{
    req->discardRequestBody();
    res->setStatusCode(405);
    res->setStatusText("POST is not allowed for this request");
    res->println("POST is forbidden for this request, try GET request");
}

void PrintStandardGETError(HTTPRequest* req, HTTPResponse* res)
{
    req->discardRequestBody();
    res->setStatusCode(405);
    res->setStatusText("GET is not allowed for this request");
    res->println("GET is forbidden for this request, try POST request");
}

void UI_LoadUserInterface(HTTPRequest* req, HTTPResponse* res)
{
    if(req->getMethod()=="GET")
        res->println(user_interface);
    else
    {
        PrintStandardPOSTError(req,res);
        return;
    }
}

void HandleAPILogin(HTTPRequest* req, HTTPResponse* res)
{
    if(req->getMethod()=="POST")
    {
        HTTPURLEncodedBodyParser parser(req);
        String provider;
        String token;

        while(parser.nextField())
        {
            std::string name = parser.getFieldName();
            if(name=="access_token")
            {
                char buf[2048];
                int len=parser.read((byte*)buf, 2048);
                token = String(buf, len);
            }
            else if(name=="provider")
            {
                char buf[64];
                int len = parser.read((byte*)buf, 64);
                provider = String(buf, len);           
            }
            else
            {
                res->println("{Error: true}");
                Logger::Warning("Login","Invalid property in POST Request");
                return;
            }
        }

        IAPI& api = APIManager.getProviderAPI(provider);
        api.SetToken(token);

        Logger::Info("API Login", "Token set succesfully for provider [" + provider +"]");
        res->println("{Error: false}");
    }
    else
    {
        PrintStandardGETError(req, res);
        return;
    }
}

void UI_LoadLoginPage(HTTPRequest* req, HTTPResponse* res)
{
    if(req->getMethod()=="GET")
    {
        res->println(login_page);
        return;
    }
    else
    {
        PrintStandardPOSTError(req, res);
        return;
    }
}