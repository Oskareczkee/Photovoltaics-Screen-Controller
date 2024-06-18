#pragma once
#include <WiFi.h>

class IAPI
{
    private:
        String _token;
    public:
        IAPI(){}
        String GetToken()const{return _token;}
        //requests login token from given provider, returns true if everything went ok
        virtual bool RequestToken(const String& username, const String& password){};
        void SetToken(String token){_token = token;}
        bool isTokenSet()const{return _token!="";}
};