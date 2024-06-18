#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
#include "Screen/pins.h"
#include <WiFi.h>
#include "cert.h"
#include "private_key.h"
#include <HTTPSServer.hpp>
#include "Networking/NetworkManager.h"
#include "Screen/ScreenManager.h"

#include <esp_netif.h>

httpsserver::SSLCert cert = httpsserver::SSLCert(
    example_crt_DER, example_crt_DER_len,
    example_key_DER, example_key_DER_len);

httpsserver::HTTPSServer STAServer = httpsserver::HTTPSServer(&cert);
httpsserver::HTTPServer APServer = httpsserver::HTTPServer();

TaskHandle_t networkT;
void networkTask(void *args);


void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_AP_STA);

    WiFi.begin("", ""); /*Wifi and password goes here*/
    NetworkManager.begin(STAServer, APServer);
    delay(5000);

    //SET CUSTOM DNS SERVER
    IPAddress googleDNS(8, 8, 8, 8); //google dns
    esp_netif_t *netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    esp_netif_dns_info_t dns_info;
    dns_info.ip.u_addr.ip4.addr = googleDNS;
    esp_netif_set_dns_info(netif, ESP_NETIF_DNS_MAIN, &dns_info);

    ScreenManager.begin();
    xTaskCreatePinnedToCore(networkTask, "Network Managing", 1024 * 75, NULL, 0, &networkT, 0); //create network task with 75kB stack, rest will be used for screen
}

void networkTask(void *args)
{
    while (true)
        NetworkManager.loop();
}

void loop(){
    ScreenManager.loop();
}