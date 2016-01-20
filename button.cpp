/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#include "button.h"
#include "wins.h"
#include "../colorextender.h"
#include "../mouse.h"
#include "../helper.h"

Button::Button(WContainer *par) :
    WComponent(par)
{
}

Button::~Button()
{

}

void Button::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    bool pressed = Mouse::isLeftDown() && aimed;
    DRAW_BOX(sb, pos, size, pressed);

    WinS::sb->drawText(text, pos, size, WinS::f, aimed ? WinS::color.hovered_text : WinS::color.text, SpriteBatch::ALIGN_CENTER);

    WComponent::Draw();
}

void Button::Update(const GameTimer& gt, const MouseState &ms)
{
    WComponent::Update(gt, ms);
}

