#pragma once
#include "../../Draw/Drawing.h"
#include "Utility/UnitConverter.h"
#include "Screen/image/sunIco.h"
#include "Screen/font/Roboto24.h"
#include "Screen/font/Roboto16.h"


class ProductionPanel : public Panel
{
  private:
    TextPanel* value;
    TextPanel* dailyValue;
  public:
    ProductionPanel(const int& posX, const int& posY, const int& width, const int& height);
    void setValues(const double& val, const double& dailyVal);
    TextPanel const* getValuePanel(){return value;}
};

void ProductionPanel::setValues(const double& val, const double& dailyVal)
{
    if(value)
        value->setText(UnitConverter::convertToPowerUnits(val));
    
    if(dailyValue)
      dailyValue->setText(UnitConverter::convertToPowerUnits(dailyVal));
}

ProductionPanel::ProductionPanel(const int& posX, const int& posY, const int& width, const int& height)
                                : Panel(posX,posY,width,height)
{
    ImagePanel* icon = new ImagePanel(0,30,new ImageData{.image = sunIco_data, .imageWidth = sunIco_width, .imageHeight = sunIco_height});
    icon->setMiddleX();
    value = new TextPanel(0, _height-110,"");
    value->setFont(&Roboto24).setMiddleX();

    dailyValue = new TextPanel(0,_height-50,"");
    dailyValue->setFont(&Roboto16).setMiddleX();

    addComponent(icon).addComponent(value).addComponent(dailyValue);
}