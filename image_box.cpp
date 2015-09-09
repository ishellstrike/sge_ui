/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

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

