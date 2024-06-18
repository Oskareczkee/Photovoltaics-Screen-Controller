#pragma once
#include <Arduino.h>
#include "IComponent.h"
#include "global_settings.h"

class TextPanel : public IComponent<TextPanel>
{
private:
    String _text;
    const GFXfont *_font = fontGlobal;

    FontProperties fp = {
        .fg_color = 0,
        .bg_color = 15,
        .fallback_glyph = 0,
        .flags = 0};

    struct TextSize
    {
        int width, height;
    };

    TextSize getTextSize()
    {
        // get bounds
        int32_t x1 = 0, y1 = 0, w = 0, h = 0;
        int32_t tmp_cur_x = _absPosX;
        int32_t tmp_cur_y = _absPosY;
        get_text_bounds(_font, _text.c_str(), &tmp_cur_x, &tmp_cur_y, &x1, &y1, &w, &h, &fp);
        return TextSize{.width = w, .height = _font->advance_y}; //get heght as font advance_y, cause height might differ for various strings, 
                                                                 //where advance_y seems to be baseline height and is constant
    }

    void beforeAdd() override
    {
        if(_parent)
            fp.bg_color = _parent->getColor(); //set background color to the parent's one, so user won't be annoyed with setting this by himself
    }
protected:
    virtual void drawBase(uint8_t* framebuffer) override;
public:

    TextPanel() : IComponent(), _text(){}
    TextPanel(const String &text) : IComponent(), _text(text)
    {
        auto size = getTextSize();
        _width = size.width;
        _height = size.height;
    }
    TextPanel(const int &posX, const int &posY, const String &text) : IComponent(posX, posY), _text(text)
    {
        auto size = getTextSize();
        _width = size.width;
        _height = size.height;
    }

    String getText() { return _text; }
    TextPanel& setText(const String &text);

    TextPanel& setFont(const GFXfont *font);
    const GFXfont *getFont() { return _font; }

    TextPanel& setColor(const uint8_t &color) { fp.fg_color = color; setUpdateFlag(); return *this;}
    uint8_t getColor() { return fp.fg_color; }

    TextPanel& setBackgroundColor(const uint8_t &color) { fp.bg_color = color; setUpdateFlag(); return *this;}
    uint8_t getBackgroundColor() { return fp.bg_color; }

    TextPanel& setWidth(const int &width) = delete;
    TextPanel& setHeight(const int &height) = delete;
    TextPanel& setSize(const int &width, const int &height) = delete;
};

void TextPanel::drawBase(uint8_t *framebuffer)
{
    int absXCpy = _absPosX, absYCpy = _absPosY; // for some reason write_mode changes positions, so we make copy
    absYCpy += _height;                         // h is text height, we add it, otherwise posY will not be applied properly

    write_mode(_font, _text.c_str(), &absXCpy, &absYCpy, framebuffer, DrawMode_t::BLACK_ON_WHITE, &fp);
}

TextPanel& TextPanel::setText(const String& text)
{
    _text = text;
    auto ts = getTextSize();
    _width=ts.width;
    setUpdateFlag();
    return *this;
}

TextPanel& TextPanel::setFont(const GFXfont *font)
{
    _font = font;
    auto ts = getTextSize();
    _width = ts.width;
    _height = _font->advance_y;
    setUpdateFlag();
    return *this;
}
