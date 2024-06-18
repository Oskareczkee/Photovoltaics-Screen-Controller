#pragma once
#include "HTTPRequest.h"

class ErrorRequest : public app::HTTPRequest
{
    public:
        ErrorRequest(const String& error,const String& response, const int& code=400): HTTPRequest()
        {
            _error = error;
            _code = code;
            _response=response;
        }
};