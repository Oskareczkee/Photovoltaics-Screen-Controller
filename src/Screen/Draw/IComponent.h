#pragma once
#include "Utility/vector.h"
#include "epd_driver.h"

typedef void* any;

/*
    Interface for implementing screen components for static screen (not scrollable)
    Set functions return reference to Component, this allows for call chains like: IComponent(...).setColor(...).setPosition(...);
    Please implement this functionality in your own classes as well, when writing setters
*/
template <class CompImpl = void*>
class IComponent
{
    protected:
        vector<IComponent<any>*> _components;//child components
        int _posX, _posY;//position relative to parent
        int _absPosX=0, _absPosY=0;//position absolute (to screen), calculated using parent's absolute position, set when adding
        int _width, _height;
        Rect_t area;//area which component takes on screen(used for updating), set when adding
        Rect_t prevArea{0,0,0,0};//area which component took frame earlier, used to clear screen area when updating

        //additional

        uint8_t _color=255;     //color in grayscale 0 - black, 255 - white
        uint8_t _flags = 0x00; //Bits:1-2 middle positioning flags
                               //     3-4 width and height flags
                               //     5   update flag   
                               //middle positioning: 00 - no positioning, 01 - middle x, 10-middle y, 11-middle both
                               //width flags: 00-no options, 01-full width x, 10-full height y, 11 full width and height
                               //update flags: 0 not updated, 1 updated, requires redraw

    public:

        //helper functions
        void checkFlags();
        void setUpdateFlag();
        void setUpdateFlag(const bool& value);

        //functions to use, when specific flags are used, do not invoke them manually, they are invoked automatically
        void posMidX();
        void posMidY();

        void fullWidth();
        void fullHeight();
        //END

        void updatePosition();//updates position of component
        void updateArea(); //updates area of component
        IComponent<any>* _parent = nullptr;
        IComponent<any>* convertToAny(){return reinterpret_cast<IComponent<any>*>(this);}
        //END helper functions

        friend class ScreenPanel;
        //draws component to given screen
        virtual void draw(uint8_t* screenBuffer);
        //draws all components that have been updated
        virtual void drawUpdated(uint8_t* screenBuffer);
        virtual void drawBase(uint8_t* framebuffer){};

        //updates internals of components, must be overriden
        virtual void update(){}

        void clearAreaToColor(uint8_t* framebuffer, const uint8_t& color);
        void clearAreaToParentColor(uint8_t* framebuffer);
        void clearArea(uint8_t* framebuffer);

        virtual void beforeAdd(){}

        template <class CompType>
        CompImpl& addComponent(IComponent<CompType>* component);
        void deleteComponents();

        

        IComponent()                     :_posX(0), _posY(0), _width(0), _height(0), _components(),
                                        area{.x=0, .y=0, .width=0, .height=0}{}

        IComponent(const int& posX, 
                  const int& posY)      :_posX(posX), _posY(posY),_width(0), _height(0), _components(),
                                        area{.x=0, .y=0,.width=0, .height=0}{}

        IComponent(const int& posX,
                  const int& posY, 
                  const int& width, 
                  const int& height)     :_posX(posX), _posY(posY),_width(width), _height(height), _components(),
                                         area{.x=0, .y=0, .width=width, .height=height}{}

        const Rect_t& getArea(){return area;}

        int getWidth(){return _width;}
        int getHeight(){return _height;}
        CompImpl& setWidth(const int& width){_width=width; area.width = width; setUpdateFlag(); return static_cast<CompImpl&>(*this);}
        CompImpl& setHeight(const int& height){_height=height; area.height = height; setUpdateFlag(); return static_cast<CompImpl&>(*this);}
        CompImpl& setSize(const int& width, const int& height){_width=width; _height=_height; setUpdateFlag(); return static_cast<CompImpl&>(*this);}

        int getPosX(){return _posX;}
        int getPosY(){return _posY;}
        int getScreenPosX(){return _absPosX;}
        int getScreenPosY(){return _absPosY;}

        CompImpl& setUpdated(){setUpdateFlag(); return static_cast<CompImpl&>(*this);}; //sets update flag to true, slightly faster than setUpdated with value
        CompImpl& setUpdated(const bool& value){setUpdateFlag(value); return static_cast<CompImpl&>(*this);} //sets updated flag, can prevent from updating if set to false
        bool isUpdated(){return _flags & 0b10000;}

        CompImpl& setPosX(const int& posX);
        CompImpl& setPosY(const int& posY);
        CompImpl& setPosition(const int& posX, const int& posY);

        uint8_t getColor(){return _color;}
        CompImpl& setColor(const uint8_t& color){_color=color; setUpdateFlag(); return static_cast<CompImpl&>(*this);}

        CompImpl& setMiddleX();//sets object in the middle of x axis of component
        CompImpl& setMiddleY();//sets object in the middle of y axis of component
        CompImpl& setMiddle();//sets object in the middle of component

        CompImpl& setFullWidth();//sets objects width to the full width of parent
        CompImpl& setFullHeight();//sets objects height to the full height of parent
        CompImpl& fillParent();//sets objects height and width to the paren's one, filling it
};

template <class CompImpl>
template <class CompType>
inline CompImpl& IComponent<CompImpl>::addComponent(IComponent<CompType>* component)
{
    if(component)
    {
        component->_parent = convertToAny();
        component->beforeAdd();
        component->checkFlags();
        _components.push_back(component->convertToAny());
    }

    return static_cast<CompImpl&>(*this);
}

template <class CompImpl>
inline void IComponent<CompImpl>::deleteComponents()
{
    for(auto& c : _components)
    {
        c->deleteComponents();// delete child components
        delete c; //delete reference to the object itself, pop_back does not delete memory
        _components.pop_back();
    }

    _components.shrink_to_fit(); //shrinks _components to minimum capacity (1)
}

template<class CompImpl>
void IComponent<CompImpl>::draw(uint8_t* screenBuffer)
{
    checkFlags();
    updatePosition();
    drawBase(screenBuffer);
    for(auto& c : _components)
        c->draw(screenBuffer);
}

template<class CompImpl>
void IComponent<CompImpl>::drawUpdated(uint8_t* screenBuffer)
{
    prevArea = area; //save previous area

    checkFlags();
    updatePosition();
    updateArea(); //this is crucial for draw updated, not so crucial in normal draw
    if(isUpdated())
    {
        epd_clear_area_cycles(prevArea, 4, 50);
        epd_fill_rect(prevArea.x, prevArea.y, prevArea.width, prevArea.height, _parent->getColor(),screenBuffer);
        drawBase(screenBuffer);
        setUpdateFlag(false);
    }
    
    for(auto& c : _components)
        c->drawUpdated(screenBuffer);
}

template<class CompImpl>
void IComponent<CompImpl>::clearArea(uint8_t* screenBuffer)
{
    epd_fill_rect(area.x, area.y, _width, _height, _color, screenBuffer);
}

template<class CompImpl>
void IComponent<CompImpl>::clearAreaToColor(uint8_t* screenBuffer, const uint8_t& color)
{
    epd_fill_rect(area.x, area.y, _width, _height, color, screenBuffer);
}

template<class CompImpl>
void IComponent<CompImpl>::clearAreaToParentColor(uint8_t* screenBuffer)
{
    if(_parent)
        epd_fill_rect(area.x, area.y, _width, _height, _parent->getColor(), screenBuffer);
}


template<class CompImpl>
inline void IComponent<CompImpl>::checkFlags()
{
    //positioning flags  00-none 01-midx 10-midy, 11-midall
    if(_flags & 0x1)
        posMidX();
    if(_flags & 0x2)
        posMidY();
    
    //width and height flags:  00-none 01-full width, 10 full height, 11 - both
    if(_flags & 0x4)
        fullWidth();
    if(_flags & 0x8)
        fullHeight();
    
    //add more here
}

template<class CompImpl>
inline void IComponent<CompImpl>::updatePosition()
{
    if(_parent)//if component has parent, update its absolute position according to parent's
    {
        _absPosX = _parent->getScreenPosX() + _posX;
        _absPosY = _parent->getScreenPosY() + _posY;
    }
    else
    {
        _absPosX = _posX;
        _absPosY = _posY;
    }
}

template<class CompImpl>
inline void IComponent<CompImpl>::updateArea()
{
    area.x = _absPosX;
    area.y = _absPosY;
    area.width = _width;
    area.height = _height;
}


template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setPosX(const int& posX)
{
    _posX=posX;
    setUpdateFlag();
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setPosY(const int& posY)
{
    _posY=posY;
    setUpdateFlag();
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setPosition(const int& posX, const int& posY)
{
    _posX=posX;
    _posY=posY;
    setUpdateFlag();
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline void IComponent<CompImpl>::posMidX()
{
    if(!_parent)
        return;
    int widthLeft = _parent->getWidth()-_width;
    int shift = widthLeft/2;

    if(shift<=0)//there is no sense in applying shift, if there is no space left
        return;

    _posX=shift;

    if(_posX!=shift) //if posX changed, set update flag
         setUpdateFlag();
}

template<class CompImpl>
inline void IComponent<CompImpl>::posMidY()
{
    if(!_parent)
        return;
    int heightLeft = _parent->getHeight()-_height;
    int shift = heightLeft/2;

    if(shift<=0)//there is no sense in applying shift, if there is no space left
        return;

    _posY = shift;

    if(_posY!=shift) //if posY changed, set update flag
        setUpdateFlag();
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setMiddleX()
{
    _flags ^= 0x1; //flip first bit
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setMiddleY()
{
    _flags ^= 0x2; //flip second bit
    return static_cast<CompImpl&>(*this);
}
template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setMiddle()
{
    _flags |= 0x1 | 0x2; //set first and second bit to true, we don't flip them, cause behavior might be weird sometimes
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setFullWidth()
{
    _flags^=0b100;
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::setFullHeight()
{
    _flags^=0b1000;
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline CompImpl& IComponent<CompImpl>::fillParent()
{
    _flags^=0b100 | 0b1000;
    return static_cast<CompImpl&>(*this);
}

template<class CompImpl>
inline void IComponent<CompImpl>::fullWidth()
{
    if(_parent)
    {
        _width = _parent->getWidth();
        if(_width!=_parent->getWidth()) //set update flag if width changed
            setUpdateFlag();
    }
}

template<class CompImpl>
inline void IComponent<CompImpl>::fullHeight()
{
    if(_parent)
    {
        _height = _parent->getHeight();
        if(_height!=_parent->getHeight()) //set update flaf if height changed
             setUpdateFlag();
    }
}

template<class CompImpl>
inline void IComponent<CompImpl>::setUpdateFlag()
{
    _flags |=0b10000;
}

template<class CompImpl>
inline void IComponent<CompImpl>::setUpdateFlag(const bool& value)
{
    _flags = _flags & ~0b10000 | (value<<5); //unset 5th bit, and set it to the value (we shift value 5 times to left, so mask will apply on 5th bit)
}
