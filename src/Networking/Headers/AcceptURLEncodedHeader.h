#pragma once
#include "HTTPHeader.h"

class AcceptURLEncodedHeader : public app::HTTPHeader
{
    public:
        AcceptURLEncodedHeader(): app::HTTPHeader("Accept", "application/x-www-form-urlencoded"){}
};