#pragma once
#include "IComponent.h"
#include "epd_driver.h"


/*
    Screen Panel represents actual screen, can be used to add and draw components
*/
class ScreenPanel : public IComponent<ScreenPanel>
{
    //ScreenPanel is friend class of IComponent, so we can use everything from IComponent class

    private:
        uint8_t* framebuffer;
        void isFramebufferOk();//checks if buffer is ok, otherwise locks program, and shows error
    public:
        ScreenPanel(const int& screenWidth, const int& screenHeight): IComponent(0,0,screenWidth, screenHeight)
                                                                                        {
                                                                                            //use malloc, ps_calloc is error prone somehow
                                                                                            framebuffer = (uint8_t *)malloc((_width * _height/2)*sizeof(uint8_t));
                                                                                            isFramebufferOk();
                                                                                            clearBuffer();
                                                                                        }

        ~ScreenPanel()
        {
            free(framebuffer);
        }
        //draws screen
        void draw();
        //draws given component on screen
        void draw(IComponent<any>* component);
        //draws all components, that have been updated
        void drawUpdated();
        //draws given component and its children, that have been updated
        void drawUpdated(IComponent<any>* component);
        
        //clears whole screen
        void clear();
        //clears to color in grayscale (0-255), 0 - black, 255 - white
        void clearToColor(const uint8_t& color);
        //clears framebuffer
        void clearBuffer();
        //clears screen, buffer and updates
        void refresh();

        int getWidth(){return _width;}
        int getHeight(){return _height;}
};

void ScreenPanel::draw()
{
    epd_poweron();
    for(auto& c : _components)
        c->draw(framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    epd_poweroff();
}

void ScreenPanel::draw(IComponent<any>* component)
{
    epd_poweron();
    component->updatePosition();
    component->draw(framebuffer);
    epd_draw_grayscale_image(component->getArea(), framebuffer);
    epd_poweroff();
}

void ScreenPanel::drawUpdated()
{
    epd_poweron();
    for(auto& c : _components)
        c->drawUpdated(framebuffer);
    epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    epd_poweroff();
}

void ScreenPanel::drawUpdated(IComponent<any>* component)
{
    epd_poweron();
    component->updatePosition();
    component->drawUpdated(framebuffer);
    epd_draw_grayscale_image(component->getArea(), framebuffer);
    epd_poweroff();
}

void ScreenPanel::clear()
{
    epd_poweron();
    epd_clear();
    epd_poweroff();
}

void ScreenPanel::clearToColor(const uint8_t& color)
{
    clear();
    memset(framebuffer, color, _width * _height / 2);//clears buffer to given color
}

void ScreenPanel::clearBuffer()
{
    memset(framebuffer, 0xFF, _width * _height / 2);
}

void ScreenPanel::refresh()
{
    clear();
    clearBuffer();
    draw();
}

void ScreenPanel::isFramebufferOk()
{
    if(!framebuffer)
        while(true)//lock program / thread
        {
            Serial.println("Framebuffer for screen buffer is not valid, Maybe there is not enough space for it?");
            delay(2000);
        }

}