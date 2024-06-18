#pragma once
#include "../../Draw/Drawing.h"
#include "Utility/UnitConverter.h"
#include "Screen/image/battery.h"
#include "Screen/font/Roboto16.h"
#include "Screen/font/firamono8.h"


class BatteryPanel : public Panel
{
    private:
        TextPanel* inValue;
        TextPanel* outValue;
        TextPanel* percent;
    public:
        BatteryPanel(const int& posX, const int& posY, const int& width, const int& height);
        void setValues(const double& inVal, const double& outVal, const int& batteryPercent);
};

void BatteryPanel::setValues(const double& inVal, const double& outVal, const int& batteryPercent)
{
    inValue->setText(UnitConverter::convertToPowerUnits(inVal));
    outValue->setText(UnitConverter::convertToPowerUnits(outVal));
    percent->setText(String(batteryPercent) + "%");
}

BatteryPanel::BatteryPanel(const int& posX, const int& posY, const int& width, const int& height)
                                : Panel(posX,posY,width,height)
{
    ImagePanel* icon = new ImagePanel(0,30,new ImageData{.image = battery_data, .imageWidth = battery_width, .imageHeight = battery_height});
    icon->setMiddleX();

    //place percent inside battery, place manually in middleY, its hard to do due battery image border
    percent = new TextPanel(0,12,"");
    percent->setMiddleX().setFont(&Roboto16);
    icon->addComponent(percent);

    Panel* valuesPanel = new Panel(0,_height-100,_width, 100);
    Panel* inPanel = new Panel(0,
                               0,
                               valuesPanel->getWidth()/2,
                               valuesPanel->getHeight());

    Panel* outPanel = new Panel(valuesPanel->getWidth()/2,
                                0,
                                valuesPanel->getWidth()/2, 
                                valuesPanel->getHeight());

    TextPanel* inTxt = new TextPanel(0,0,"IN");
    inTxt->setMiddleX().setFont(&FiraMono8);

    TextPanel* outTxt = new TextPanel(0,0,"OUT");
    outTxt->setMiddleX().setFont(&FiraMono8);

    inValue = new TextPanel(0,0,"");
    inValue->setMiddle().setFont(&Roboto16);
    outValue = new TextPanel(0,0,"");
    outValue->setMiddle().setFont(&Roboto16);

    valuesPanel->addComponent(inPanel).addComponent(outPanel);
    inPanel->addComponent(inTxt).addComponent(inValue);
    outPanel->addComponent(outTxt).addComponent(outValue);


    addComponent(icon).addComponent(valuesPanel);
}