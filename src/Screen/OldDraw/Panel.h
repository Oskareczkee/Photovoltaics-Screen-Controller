#pragma once
#include "IDrawable.h"
#include "epd_driver.h"

class Panel : public IDrawable
{
    public:
        using IDrawable::IDrawable; //inherit constructors
        virtual void draw() override
        {
            epd_fill_rect(_posX, _posY, _width, _height, 0, framebuffer);
            IDrawable::draw();
        }
};