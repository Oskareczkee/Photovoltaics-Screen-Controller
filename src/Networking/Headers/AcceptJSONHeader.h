#pragma once
#include "HTTPHeader.h"

class AcceptJSONHeader : public app::HTTPHeader
{
    public:
        AcceptJSONHeader(): app::HTTPHeader("Accept", "application/json"){}
};