#pragma once
#include "API/IAPI.h"
#include "API/SolarmanAPI.h"

/*Static class containing API provider names*/
struct APIProviders
{
    const static String Default;
    const static String Solarman;
};

const String APIProviders::Solarman = "Solarman";
const String APIProviders::Default = "Solarman";

class APIManagerClass
{
    private:
        SolarmanAPI _solarman;
    public:
        SolarmanAPI& getSolarman(){return _solarman;}

        //Gets and returns provider by name, if not found returns APIProviders::Default Provider
        IAPI& getProviderAPI(const String& provider_name);
}APIManager;


IAPI& APIManagerClass::getProviderAPI(const String& provider_name)
{
    if(provider_name==APIProviders::Solarman)
        return _solarman;
    else
        return _solarman; //default provider
}