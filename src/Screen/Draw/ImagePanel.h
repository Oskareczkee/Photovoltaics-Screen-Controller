#pragma once
#include "IComponent.h"
#include "epd_driver.h"

struct ImageData
{
    const uint8_t *image;
    const uint32_t &imageWidth;
    const uint32_t &imageHeight;
};

class ImagePanel : public IComponent<ImagePanel>
{
private:
    const ImageData *_image;
protected:
    virtual void drawBase(uint8_t* framebuffer) override;
public:
    ImagePanel(const ImageData *image) : IComponent(), _image(image)
    {
        _width = _image->imageWidth;
        _height = image->imageHeight;
    }

    ImagePanel(const int &posX, const int &posY, const ImageData *image) : IComponent(posX, posY), _image(image)
    {
        _width = _image->imageWidth;
        _height = image->imageHeight;
    }
    
    const ImageData& getImage(){return *_image;}
    ImagePanel& setImage(const ImageData* data){_image=data; setUpdateFlag(); return *this;}

    ImagePanel& setWidth(const int &width) = delete;
    ImagePanel& setHeight(const int &height) = delete;
    ImagePanel& setSize(const int &width, const int &height) = delete;
};

void ImagePanel::drawBase(uint8_t* framebuffer)
{
        Rect_t area = {
        .x = _absPosX,
        .y = _absPosY,
        .width = _image->imageWidth,
        .height = _image->imageHeight};

    epd_copy_to_framebuffer(area, (uint8_t *)_image->image, framebuffer); // remove const modifier (required by library)
}
