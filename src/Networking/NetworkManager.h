#pragma once
#include <WString.h>
#include <WiFi.h>
#include "STA/STAManager.h"
#include "AP/APManager.h"
#include "Requests/RequestManager.h"
#include "API/SolarmanAPI.h"
#include "cert.h"
#include "private_key.h"
#include "Utility/Logger.h"
#include "APIManager.h"

using namespace httpsserver;

class NetworkManagerClass
{
    private:
        bool _isAPSetup=false;
        bool _isSTASetup=false;

        STAManager* _sta;
        APManager* _ap;
        HTTPSServer* _STAServer;
        HTTPServer* _APServer;

        bool isReady();

    public:
        NetworkManagerClass(HTTPSServer* STAServer, HTTPServer* APServer):  _sta(new STAManager(*STAServer)), 
                                                                            _ap(new APManager(*APServer)), 
                                                                            _STAServer(STAServer), 
                                                                            _APServer(APServer){}
        NetworkManagerClass(): _sta(nullptr),
                               _ap(nullptr),
                               _STAServer(nullptr),
                               _APServer(nullptr){}                                                                                
        ~NetworkManagerClass()
        {
            delete _sta;
            delete _ap;//servers are references to pointers, so we do not manage them
        }

        void loop();
        void setup();
        void begin(HTTPSServer& STAServer, HTTPServer& APServer);

        const STAManager& getSTAManager()const{return *_sta;}
        const APManager& getAPManager()const{return *_ap;}

        bool isAP()const{return _isAPSetup;}
        bool isSTA()const{return _isSTASetup;}
}NetworkManager;

inline void NetworkManagerClass::setup()
{
    _STAServer->start();
    _APServer->start();
}

inline void NetworkManagerClass::begin(HTTPSServer& STAServer, HTTPServer& APServer)
{
    _sta = new STAManager(STAServer);
    _ap = new APManager(APServer);
    _STAServer = &STAServer;
    _APServer= &APServer;
    setup();
}

inline void NetworkManagerClass::loop()
{
    if(!isReady())
    {
        delay(500);
        return;
    }
    
    if(WiFi.status()!=WL_CONNECTED && !_isAPSetup){
        _ap->SetupAP("esp32 test", "youshallnotpass");
        _isAPSetup=true;
        _isSTASetup=false;
    }
    
    if(WiFi.status()==WL_CONNECTED && !_isSTASetup)
    {
        _sta->SetupSTA();
        _isSTASetup=true;
        _isAPSetup=false;
        Logger::Info("Log into https://" + WiFi.localIP().toString());
    }

    if(_isAPSetup)
        _APServer->loop();
    
    else if(_isSTASetup)
        _STAServer->loop();
}

inline bool NetworkManagerClass::isReady()
{
    if(_sta==nullptr || _ap==nullptr || _STAServer==nullptr || _APServer==nullptr)
    {
        Logger::Error("Network Manager is not initialized");
        return false;
    }
    return true;
}
