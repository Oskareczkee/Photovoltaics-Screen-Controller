#pragma once
#include <Arduino.h>

/*  
    static class with methods allowing to convert various units to proper string
*/
class UnitConverter
{
    public:
        static String convertToPowerUnits(const double& value, const int& decimalPlaces=2);
        static String convertToVoltageUnits(const double& value, const int& decimalPlaces=2);
        static String convertToCurrentUnits(const double& value, const int& decimalPlaces=2);
        static String convertToFrequencyUnits(const double& value, const int& decimalPlaces=2);
};

String UnitConverter::convertToPowerUnits(const double& value, const int& decimalPlaces)
{
    double copy = value;
    if(copy < 1000.0)
        return String(copy, decimalPlaces) + " W";
    
    copy/=1000.0;
    if(copy < 1000.0)
        return String(copy,decimalPlaces) + " kW";
    
    copy/=1000.0;
    return String(copy,decimalPlaces) + " MW"; 
}

String UnitConverter::convertToVoltageUnits(const double& value, const int& decimalPlaces)
{
    double copy = value;

        if(copy < 1000.0)
        return String(copy, decimalPlaces) + " V";
    
    copy/=1000.0;
    if(copy < 1000.0)
        return String(copy,decimalPlaces) + " kV";
    
    copy/=1000.0;
    return String(copy,decimalPlaces) + " MV"; 
}

String UnitConverter::convertToCurrentUnits(const double& value, const int& decimalPlaces)
{
    double copy = value;

    //convert to mili amps if value is less than 1
    if(copy < 1.0)
    {
        copy*=100;
        if(copy< 1000.0)
            return String(copy, decimalPlaces) + " mA";
    }

    if(copy < 1000.0)
        return String(copy, decimalPlaces) + " A";
    
    copy/=1000.0;
    if(copy < 1000.0)
        return String(copy,decimalPlaces) + " kA";
    
    copy/=1000.0;
    return String(copy,decimalPlaces) + " MA";
}

String UnitConverter::convertToFrequencyUnits(const double& value, const int& decimalPlaces)
{
    double copy = value;

    if(copy < 1000.0)
        return String(copy,decimalPlaces) +"Hz";
    copy/=1000.0;

    if (copy<1000.0)
        return String(copy, decimalPlaces) + "kHz";
    
    copy/=1000.0;

    return String(copy, decimalPlaces) + "MHz";
}