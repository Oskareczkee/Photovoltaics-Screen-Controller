#pragma once 

#include "../Draw/Drawing.h"
#include "../font/firamono8.h"
#include "../image/wifi-0.h"
#include "../image/wifi-1.h"
#include "../image/wifi-2.h"
#include "../image/wifi-3.h"
#include "../image/wifi-4.h"
#include "WiFi.h"
#include "time.h"
#include "esp_adc_cal.h"
#include "../pins.h"

class TopPanel : public Panel
{
    private:
        //components, add them as you wish, keep here the most important ones to keep references to them for easy updating
        TextPanel* logo = nullptr;
        TextPanel* date = nullptr;
        ImagePanel* wifiStrengthIcon = nullptr;
        TextPanel* networkName = nullptr;
        TextPanel* batteryCondition = nullptr;

        String getHostName();
        String getDate();
        String getBatteryUse();

        const int networkNameMaxChars=10;
        const char* ntpServer = "pool.ntp.org";
        const long gmtOffsetSec = 0;
        const int daylightOffsetSec = 3600;

        const ImageData* getConnectionStrengthImage();
    public:
        //if component will have size scalable with scree add constructor with screen panel, otherwise you don't have to
        TopPanel(const int& width, const int& height);
        virtual void update() override;
};

void TopPanel::update()
{
    date->setText(getDate());
    wifiStrengthIcon->setImage(getConnectionStrengthImage());
    networkName->setText(getHostName());
    batteryCondition->setText(getBatteryUse());
}

const ImageData* TopPanel::getConnectionStrengthImage()
{
    if(WiFi.status()!=WL_CONNECTED)
        return new ImageData{.image = wifi0_data, .imageWidth = wifi0_width, .imageHeight=wifi0_height};
    
    int rssi = WiFi.RSSI();

    if(rssi <= -90)     //very poor connection
        return new ImageData{.image = wifi0_data, .imageWidth = wifi0_width, .imageHeight=wifi0_height};
    else if(rssi > -90 && rssi < -80)   //bad connection
        return new ImageData{.image = wifi1_data, .imageWidth = wifi1_width, .imageHeight=wifi1_height};
    else if(rssi > -80 && rssi < -67)   //ok connection
        return new ImageData{.image = wifi2_data, .imageWidth = wifi2_width, .imageHeight=wifi2_height};
    else if(rssi > -67 && rssi < -50)   //good connection
        return new ImageData{.image = wifi3_data, .imageWidth = wifi3_width, .imageHeight=wifi3_height};
    else    //excelent connection
        return new ImageData{.image = wifi4_data, .imageWidth = wifi4_width, .imageHeight=wifi4_height};
}

String TopPanel::getBatteryUse()
{
    int vref = 1100;
    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
        ADC_UNIT_2,
        ADC_ATTEN_DB_11,
        ADC_WIDTH_BIT_12,
        1100,
        &adc_chars
    );
    if(val_type==ESP_ADC_CAL_VAL_EFUSE_VREF)
        vref = adc_chars.vref;

    uint16_t v = analogRead(BATT_PIN);
    float voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
    float percent = (voltage/5.0)*100;

    return String(percent) + "%";
}

String TopPanel::getHostName()
{
    if(WiFi.status()!=WL_CONNECTED)
        return "...";

    String host = WiFi.SSID();
    String output;

    for(int x =0;x<networkNameMaxChars && x < host.length();x++)
        output+=host[x];
    
    if(output.length() < host.length())
        output+="...";
    
    return output;
}

String TopPanel::getDate()
{
    if(WiFi.status()!=WL_CONNECTED)
        return "...";

    configTime(gmtOffsetSec, daylightOffsetSec, ntpServer);

    tm timeinfo;
    if(!getLocalTime(&timeinfo))
        return "...";

    char strBuf[30];
    strftime(strBuf, sizeof(strBuf), "%a %D", &timeinfo);

    return String(strBuf);
}

TopPanel::TopPanel(const int& width, const int& height) : Panel(0,0,width,height)
{
    setFullWidth().setColor(0x00);

    Panel* networkData =  new Panel(_width-500,0,500,_height);
    networkData->setColor(0x00);

    logo = new TextPanel(30,0,"Sunwindgen");
    logo->setColor(0xff).setFont(&FiraMono8).setMiddleY();


    int padding =0;
    String dateStr = getDate();
    date = new TextPanel(30,5,dateStr);
    date->setColor(0xff).setFont(&FiraMono8).setMiddleY();

    padding+=30 + date->getWidth();

    String hostName = getHostName();
    networkName = new TextPanel(padding+30,5,hostName);
    networkName->setColor(0xff).setFont(&FiraMono8).setMiddleY();

    padding+=30+networkName->getWidth();

    auto img = getConnectionStrengthImage();
    wifiStrengthIcon = new ImagePanel(padding+30,5,img);
    wifiStrengthIcon->setMiddleY();

    padding+=30 + wifiStrengthIcon->getWidth();
    
    String batteryPercent = getBatteryUse();
    batteryCondition = new TextPanel(padding+30,5,batteryPercent);
    batteryCondition->setColor(0xff).setFont(&FiraMono8).setMiddleY();

    addComponent(networkData);
    addComponent(logo);
    networkData->addComponent(date).addComponent(wifiStrengthIcon).addComponent(networkName).addComponent(batteryCondition);
}