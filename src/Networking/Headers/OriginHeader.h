#pragma once
#include "HTTPHeader.h"

class OriginHeader : public app::HTTPHeader
{
    private:
    public:
        OriginHeader(const String& origin): app::HTTPHeader("Origin", origin){}
        OriginHeader():app::HTTPHeader("Origin", ""){}
        //set origin using set value, get origin using get value
};