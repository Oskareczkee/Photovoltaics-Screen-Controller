#pragma once
#include "../../Draw/Drawing.h"
#include "Utility/UnitConverter.h"
#include "Screen/image/gridIco.h"
#include "Screen/font/Roboto16.h"
#include "Screen/font/roboto14.h"
#include "Screen/font/firamono8.h"


class GridPanel : public Panel
{
    private:
        TextPanel* inValue;
        TextPanel* outValue;

        TextPanel* inDailyValue;
        TextPanel* outDailyValue;
    public:
        GridPanel(const int& posX, const int& posY, const int& width, const int& height);
        void setValues(const double& inVal, const double& outVal, const double& inDaily, const double& outDaily);
        void setInValue(const double& inVal);
        void setInValues(const double& inVal, const double& inDailyVal);
        void setOutValue(const double& outVal);
        void setOutValues(const double& outVal, const double& outDailyVal);
        TextPanel const* getInValuePanel(){return inValue;}
        TextPanel const* getOutValuePanel(){return outValue;}
};

void GridPanel::setValues(const double& inVal, const double& outVal, const double& inDaily, const double& outDaily)
{
    setInValues(inVal, inDaily);
    setOutValues(outVal, outDaily);
}

void GridPanel::setInValue(const double& inVal)
{
    if(inValue)
        inValue->setText(UnitConverter::convertToPowerUnits(inVal));
}

void GridPanel::setOutValue(const double& outVal)
{
    if(outValue)
        outValue->setText(UnitConverter::convertToPowerUnits(outVal));
}

void GridPanel::setInValues(const double& inVal, const double& inDailyVal)
{
    setInValue(inVal);

    if(inDailyValue)
        inDailyValue->setText(UnitConverter::convertToPowerUnits(inDailyVal));
}

void GridPanel::setOutValues(const double& outVal, const double& outDailyVal)
{
    setOutValue(outVal);

    if(outDailyValue)
        outDailyValue->setText(UnitConverter::convertToPowerUnits(outDailyVal));
}

GridPanel::GridPanel(const int& posX, const int& posY, const int& width, const int& height)
                                : Panel(posX,posY,width,height)
{
    ImagePanel* icon = new ImagePanel(0,30,new ImageData{.image = gridIco_data, .imageWidth = gridIco_width, .imageHeight = gridIco_height});
    icon->setMiddleX();
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

    inValue = new TextPanel(0,20,"");
    inValue->setMiddleX().setFont(&Roboto16);
    outValue = new TextPanel(0,20,"");
    outValue->setMiddleX().setFont(&Roboto16);

    inDailyValue = new TextPanel(0,55,"");
    inDailyValue->setMiddleX().setFont(&Roboto14);
    outDailyValue = new TextPanel(0,55,"");
    outDailyValue->setMiddleX().setFont(&Roboto14);

    valuesPanel->addComponent(inPanel).addComponent(outPanel);
    inPanel->addComponent(inTxt).addComponent(inValue).addComponent(inDailyValue);
    outPanel->addComponent(outTxt).addComponent(outValue).addComponent(outDailyValue);

    addComponent(icon).addComponent(valuesPanel);
}