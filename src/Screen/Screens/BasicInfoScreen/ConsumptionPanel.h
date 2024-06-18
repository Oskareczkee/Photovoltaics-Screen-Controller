#pragma once
#include "../../Draw/Drawing.h"
#include "Utility/UnitConverter.h"
#include "Screen/image/consumptionIco.h"
#include "Screen/font/Roboto24.h"


class ConsumptionPanel : public Panel
{
    private:
        TextPanel* value;
        TextPanel* dailyValue; 
    public:
        ConsumptionPanel(const int& posX, const int& posY, const int& width, const int& height);
        void setValues(const double& value, const double& dailyVal);
        TextPanel const* getValuePanel(){return value;}
};

void ConsumptionPanel::setValues(const double& val, const double& dailyVal)
{
    if(value)
        value->setText(UnitConverter::convertToPowerUnits(val));

    if(dailyValue)
        dailyValue->setText(UnitConverter::convertToPowerUnits(dailyVal));
}

ConsumptionPanel::ConsumptionPanel(const int& posX, const int& posY, const int& width, const int& height)
                                : Panel(posX,posY,width,height)
{
    ImagePanel* icon = new ImagePanel(0,30,new ImageData{.image = consumptionIco_data, .imageWidth = consumptionIco_width, .imageHeight = consumptionIco_height});
    icon->setMiddleX();
    value = new TextPanel(0, _height-110,"");
    value->setFont(&Roboto24).setMiddleX();

    dailyValue = new TextPanel(0,_height-50,"");
    dailyValue->setFont(&Roboto16).setMiddleX();

    addComponent(icon).addComponent(value).addComponent(dailyValue);
}