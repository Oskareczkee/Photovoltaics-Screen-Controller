#pragma once
#include "IComponent.h"
#include "epd_driver.h"

class Border : public IComponent<Border>
{
    protected:
        //before add set component's width and height to parent's
        void beforeAdd()override
        {
            _width=_parent->getWidth();
            _height =_parent->getHeight();
        }

    private:
        int _thickness=1;
    public:
        Border(const int& thickness=1): IComponent(0,0), _thickness(thickness){}
        int getThickness(){return _thickness;}
        Border& setThickness(const int& thickness){_thickness=thickness; setUpdateFlag(); return *this;}
        virtual void drawBase(uint8_t* framebuffer) override;
};

void Border::drawBase(uint8_t* framebuffer)
{
        //we draw rectangle, another rectangle etc, till we get thick enough rectangle
        for(int x =0;x<_thickness;x++)
            epd_draw_rect(_absPosX-x-1, _absPosY-x-1, _width+(x*2), _height+(x*2), _color, framebuffer);
}