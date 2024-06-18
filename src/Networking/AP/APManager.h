#pragma once
#include <WiFi.h>
#include <HTTPSServer.hpp>
#include "APHandlers.h"

using namespace httpsserver;

class APManager
{
    private:
        HTTPServer& _server;
        ResourceNode* _getNetworksNode = new ResourceNode("/get-networks", "GET", &handleGetNetworks);
        ResourceNode* _getNetworkLoginNode = new ResourceNode("/", "GET", &handleNetworkLogin);
        ResourceNode* _postNetworkLoginNode = new ResourceNode("/", "POST", &handleNetworkLogin);

    public:
        APManager(HTTPServer& Server): _server(Server){}
        void SetupAP(const String& ssid, const String& password);
};

void APManager::SetupAP(const String& ssid, const String& password)
{
    WiFi.softAP(ssid, password);
    IPAddress ip=WiFi.softAPIP();
    _server.registerNode(_getNetworksNode);
    _server.registerNode(_getNetworkLoginNode);
    _server.registerNode(_postNetworkLoginNode);
}