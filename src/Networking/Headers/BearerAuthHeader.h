#pragma once
#include "HTTPHeader.h"

class BearerAuthHeader : public app::HTTPHeader
{
    public:
        BearerAuthHeader(): HTTPHeader("Authorization", "Bearer "){}
        BearerAuthHeader(const String& bearerToken): app::HTTPHeader("Authorization", "Bearer "+bearerToken){}
        void SetBearerToken(const String& bearerToken){_value+=bearerToken;}
};