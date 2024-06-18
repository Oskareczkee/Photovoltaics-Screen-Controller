#pragma once
#include "IDrawable.h"
#include "epd_driver.h"

class ScreenPanel : public IDrawable
{
    public:
        ScreenPanel(const int& screenWidth, const int& screenHeight): IDrawable(0,0, screenWidth, screenHeight){}
        void draw() override
        {
            IDrawable::draw();
            epd_poweron();
            epd_fill_rect(100, 100, 50, 50, 0, framebuffer);
            epd_draw_grayscale_image(epd_full_screen(), framebuffer);
            epd_poweroff();
            delay(3000);
        }
};