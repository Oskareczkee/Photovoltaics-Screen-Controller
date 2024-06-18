#pragma once
#include "Arduino.h"
#include "Utility/vector.h"
#include "epd_driver.h"
#include "esp32/spiram.h"

class IDrawable
{
    protected:
        int _posX, _posY;//position are  relative to the component in which this component is
        int _width, _height;
        uint8_t *framebuffer=nullptr;
        Rect_t area;
        vector<IDrawable*> _components;
        IDrawable* _parent=nullptr;

        void resetFramebuffer(){ memset(framebuffer, 0xFF, _width * _height / 2);}
        void isFramebufferOk()//checks if framebuffer is ok, otherwise locks program
        {
            if(!framebuffer)
                while(true)
                {
                    Serial.println("Framebuffer for component is not valid");
                    delay(2000);
                }
        }
    public:
        virtual void draw();

        IDrawable()                     :_posX(0), _posY(0), _width(0), _height(0), _components(),
                                        area{.x=_posX, .y=_posY, .width=_width, .height=_height}
                                        {
                                            framebuffer = (uint8_t *)malloc((_width * _height/2)*sizeof(uint8_t));
                                            isFramebufferOk();
                                            resetFramebuffer();
                                        }

        IDrawable(const int& posX, 
                  const int& posY)      :_posX(posX), _posY(posY),_width(0), _height(0), _components(),
                                        area{.x=_posX, .y=_posY, .width=_width, .height=_height} 
                                        {
                                            framebuffer=(uint8_t *)malloc((_width * _height/2)*sizeof(uint8_t));
                                            isFramebufferOk();
                                            resetFramebuffer();
                                        }

        IDrawable(const int& posX,
                  const int& posY, 
                  const int& width, 
                  const int& height)     :_posX(posX), _posY(posY),_width(width), _height(height), _components(),
                                         area{.x=_posX, .y=_posY, .width=_width, .height=_height} 
                                         {
                                            framebuffer=(uint8_t *)malloc((_width * _height/2)*sizeof(uint8_t));
                                            isFramebufferOk();
                                            resetFramebuffer();
                                         }

        ~IDrawable()
        {
            free(framebuffer);
        }

        int getPosX(){return _posX;}
        int getPosY(){return _posY;}
        void setPosX(const int& posX){_posX=posX;}
        void setPosY(const int& posY){_posY=posY;}

        int getWidth(){return _width;}
        int getHeight(){return _height;}
        void setWidth(const int& width){_width=width;}
        void setHeight(const int& height){_height=height;}

        Rect_t getArea(){return area;}

        IDrawable& getParent(){return *_parent;}
        void setParent(IDrawable* parent){_parent=parent;}


        void addComponent(IDrawable* component)
        {
            component->setParent(this);
            _components.push_back(component);
        }
};
void IDrawable::draw()
{
    if(framebuffer==nullptr)
        return;
    
    for(auto&c : _components)
    {
        c->draw();    
        epd_copy_to_framebuffer(c->area, c->framebuffer, _parent->framebuffer);
    }

    if(_parent == nullptr)
        return;

    //epd_copy_to_framebuffer(area, framebuffer, _parent->framebuffer);
}