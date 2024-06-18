#pragma once
#include "../../Draw/Drawing.h"
#include "../../font/firamono8.h"
#include "../TopPanel.h"
#include "../../../Networking/APIManager.h"
#include "ProductionPanel.h"
#include "ConsumptionPanel.h"
#include "GridPanel.h"
#include "DetailPanel.h"
#include "BatteryPanel.h"

class BasicInfoPanel : public Panel
{
  private:
    TopPanel* topPanel;
    ProductionPanel* production;
    ConsumptionPanel* consumption;
    GridPanel* grid;
    DetailPanel* detail;
    BatteryPanel* battery;

    long stationID = 60672993;
    long deviceID = 225671663;
  public:
    BasicInfoPanel(const int& posX, const int& posY, const int& width, const int& height);
    virtual void update() override;
};

void BasicInfoPanel::update()
{
   auto info = APIManager.getSolarman().getStationInfo(60672993);
   auto details = APIManager.getSolarman().getDeviceDetail(60672993,225671663);
   auto daily  = APIManager.getSolarman().getStationDailyUsage(60672993);

   consumption->setValues(info.Consumption, daily.consumption);
   production->setValues(info.Production, daily.production);
   grid->setValues(info.toGridPower, info.fromGridPower, daily.gridIn, daily.gridOut);
   battery->setValues(info.batteryCharge, info.batteryDischarge, info.batteryPercent);
   detail->setValues(details);

   topPanel->update();
}

BasicInfoPanel::BasicInfoPanel(const int& posX, const int& posY, const int& width, const int& height)
                :Panel(posX, posY, width, height)
{
   topPanel=new TopPanel(getWidth(), getHeight()/10);
   addComponent(topPanel);
   auto info = APIManager.getSolarman().getStationInfo(60672993);
   auto details = APIManager.getSolarman().getDeviceDetail(60672993,225671663);
   auto daily  = APIManager.getSolarman().getStationDailyUsage(60672993);

   const int marginTop=10, marginX=5;

   production= new ProductionPanel(
        marginX,
        getHeight()/10 + marginTop,
        getWidth()/3-marginX*2,
        (getHeight()- getHeight()/10)/2 - marginTop);\

   consumption = new ConsumptionPanel(
    getWidth()/3 * 1 + marginX,
    getHeight()/10+marginTop,
    getWidth()/3-marginX*2,
    (getHeight()- getHeight()/10)/2 - marginTop);

    grid= new GridPanel(
    getWidth()/3*2 + marginX,
    getHeight()/10 + marginTop,
    getWidth()/3-marginX*2,
    (getHeight()-getHeight()/10)/2 - marginTop);

    detail= new DetailPanel(
     marginX,
     getHeight()/10 + (getHeight()-getHeight()/10)/2 + marginTop,
     getWidth()*(2.0/3)-marginX*2,
     (getHeight()-getHeight()/10)/2 - marginTop*2);

   battery = new BatteryPanel(
      getWidth()/3*2 + marginX,
      getHeight()/10 + (getHeight()-getHeight()/10)/2 + marginTop,
      getWidth()/3 - marginX*2,
      (getHeight()-getHeight()/10)/2 - marginTop*2);

   consumption->setValues(info.Consumption, daily.consumption);
   production->setValues(info.Production, daily.production);
   grid->setValues(info.toGridPower, info.fromGridPower, daily.gridIn, daily.gridOut);
   battery->setValues(info.batteryCharge, info.batteryDischarge, info.batteryPercent);
   detail->setValues(details);

   addComponent(production);
   addComponent(consumption);
   addComponent(grid);
   addComponent(battery);
   addComponent(detail);
}
