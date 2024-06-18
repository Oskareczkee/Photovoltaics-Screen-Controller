#pragma once
#include "HTTPHeader.h"

class TypeJSONHeader : public app::HTTPHeader
{
    public:
        TypeJSONHeader(): app::HTTPHeader("Content-Type", "application/json"){}
};