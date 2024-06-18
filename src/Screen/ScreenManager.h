#pragma once
#include <Arduino.h>
#include "epd_driver.h"
#include "Draw/Drawing.h"
#include "Screens/BasicInfoScreen/BasicInfo.h"

class ScreenManagerClass
{
    private:
        const int _screenWidth = EPD_WIDTH;
        const int _screenHeight = EPD_HEIGHT;
        int actualScreen=0;
        const int SCREEN_COUNT=1;

        ScreenPanel screen;
        BasicInfoPanel* basicInfo;

    public:
        ScreenManagerClass():screen(_screenWidth, _screenHeight){}

        int getWidth(){return _screenWidth;}
        int getHeight(){return _screenHeight;}

        void begin();
        void setup();
        void loop();
}ScreenManager;

void ScreenManagerClass::setup()
{
    epd_init();
    screen.clearToColor(0xff-64);
    basicInfo =  new BasicInfoPanel(0,0,screen.getWidth(), screen.getHeight());
    screen.addComponent(basicInfo);
    screen.draw();
}

void ScreenManagerClass::begin()
{
    setup();
}

void ScreenManagerClass::loop()
{
    screen.draw();
    delay(15000);
    screen.clearToColor(0xff - 64);
    basicInfo->update();
}