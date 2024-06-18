#pragma once
#include <WString.h>

namespace app{
    enum class HTTPRequestType
    {
        NONE,
        GET,
        POST
    };

    class HTTPRequest
    {
        protected:
            HTTPRequestType _type;
            String _response;
            String _error;
            int _code;
        public:
            HTTPRequest(const HTTPRequestType& type, const String& response, const int& code):_type(type), _response(response), _code(code){}
            HTTPRequest(): _type(HTTPRequestType::NONE), _response(String()), _code(400){} //400 is basic error code
            String GetResponse() const {return _response;}
            HTTPRequestType GetType() const {return _type;}
            String GetError() const {return _error;}
            int ReturnCode() const {return _code;}
            bool isError() const {return _code<200 || _code > 299 || _type==HTTPRequestType::NONE;}// 200-299 is success response, any other will be treated as error

    };
}