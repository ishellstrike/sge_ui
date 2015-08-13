#include "image_box.h"

ImageBox::ImageBox(WContainer *par) :
    WComponent(par)
{
}

void ImageBox::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    if(tex)
        sb.drawQuad(pos, size, *tex, color);
    else
        sb.drawRect(pos, size, color);

    WComponent::Draw();
}

void ImageBox::Update(const GameTimer &gt)
{
    WComponent::Update(gt);
}

