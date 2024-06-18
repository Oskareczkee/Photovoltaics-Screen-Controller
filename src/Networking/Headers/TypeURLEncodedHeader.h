#pragma once
#include "HTTPHeader.h"

class TypeURLEncodedHeader : public app::HTTPHeader
{
    public:
        TypeURLEncodedHeader(): app::HTTPHeader("Content-Type", "application/x-www-form-urlencoded"){}
};