/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#include "label.h"
#include "wins.h"
#include "../colorextender.h"

Label::Label(WContainer *par) :
    WComponent(par)
{
    size = {20,20};
    text("empty");
    wcomponent_type = "label";
}

Label::~Label()
{

}

void Label::text(const std::string &__s)
{
    m_text = __s;
    size = WinS::sb->measureText(m_text, WinS::f);
}

void Label::align(const SpriteBatch::ALIGN __a)
{
    m_align = __a;
}

const std::string Label::text() const
{
    return m_text;
}

void Label::append(const std::string &__s)
{
    m_text.append(__s);
    size = WinS::sb->measureText(m_text, WinS::f);
}

void Label::Draw() const
{
    glm::vec2 p = globalPos();
    if(!onMouseClick.empty() && aimed)
        WinS::sb->drawText(m_text, p, size, WinS::f, WinS::color.hovered_text, m_align);
    else
        WinS::sb->drawText(m_text, p, size, WinS::f, WinS::color.text, m_align);

    WComponent::Draw();
}

void Label::Update(const GameTimer& gt, const MouseState &ms)
{
    WComponent::Update(gt, ms);
}
