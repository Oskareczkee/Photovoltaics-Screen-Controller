#pragma once
#include <WString.h>

namespace app{
    class HTTPHeader
    {
        protected:
            String _name;
            String _value;
        public:
            HTTPHeader(const String& name, const String& value): _name(name), _value(value){}
            HTTPHeader(): _name(String()), _value(String()){}
            String GetName()const {return _name;}
            String GetValue(){return  _value;}
    };
}