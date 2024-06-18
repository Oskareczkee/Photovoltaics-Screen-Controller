#pragma once

struct DCInfo
{
    double voltage;
    double current;
    double power;
};

struct ACInfo
{
    double voltage;
    double current;
};

struct DeviceDetail
{
  public:
    DCInfo PV1;
    DCInfo PV2;
    //also called L1
    ACInfo R;
    //also called L2
    ACInfo S;
    //also called L3
    ACInfo T;
    double RFrequency;
};