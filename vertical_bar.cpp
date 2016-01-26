/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#include "vertical_bar.h"
#include "../spritebatch.h"
#include "../colorextender.h"
#include "wins.h"

VerticalBar::VerticalBar(WContainer* par) :
    WComponent(par)
{

}

VerticalBar::~VerticalBar()
{

}

void VerticalBar::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    float nsize = size.y - 4;
    sb.drawRect(pos + glm::vec2(1, 3) + glm::vec2(0, nsize*top), size - glm::vec2(4) - glm::vec2(0, nsize*top + nsize*(1-bot)), WinS::color.border_up);

    WComponent::Draw();
}

void VerticalBar::Update(const GameTimer &gt, const MouseState &ms)
{
    WComponent::Update(gt, ms);
}

