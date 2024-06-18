#pragma once
#include "IComponent.h"

class Panel : public IComponent<Panel>
{
    protected:
        virtual void drawBase(uint8_t* framebuffer) override;
    public:
        using IComponent::IComponent; //inherit constructors
};

void Panel::drawBase(uint8_t* framebuffer)
{
    epd_fill_rect(_absPosX, _absPosY, _width, _height, _color, framebuffer);
}