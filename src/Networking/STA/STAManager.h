#pragma once
#include <WiFi.h>
#include <HTTPSServer.hpp>
#include "STAHandlers.h"
#include "Utility/Logger.h"

using namespace httpsserver;

class STAManager
{
    private:
        HTTPSServer& _server;
        ResourceNode* _userInterfaceNode= new ResourceNode("/", "GET", &UI_LoadUserInterface);
        ResourceNode* _getLoginNode = new ResourceNode("/login", "GET", &UI_LoadLoginPage);
        ResourceNode* _postLoginNode = new ResourceNode("/api-login", "POST", &HandleAPILogin);
    public:
        STAManager(HTTPSServer& server): _server(server){}
        void SetupSTA();
        bool isConnected() const {return WiFi.status()==WL_CONNECTED;}
};

void STAManager::SetupSTA()
{
    if(!isConnected())
    {
        Logger::Warning("STA","WiFi connection is not established");
        return;
    }

    _server.registerNode(_userInterfaceNode);
    _server.registerNode(_getLoginNode);
    _server.registerNode(_postLoginNode);
}