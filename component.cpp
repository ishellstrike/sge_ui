/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#include "wins.h"
#include "component.h"
#include "../mouse.h"
#include "../helper.h"


WComponent::WComponent(WContainer *par)
{
    parent = par;
    if(parent)
    {
        parent->Items.push_back(std::shared_ptr<WComponent>(this));
        weak_this = parent->Items.back();
    }
}

WComponent::~WComponent()
{

}

void WComponent::Draw() const
{

}

void WComponent::Update(const GameTimer &, const MouseState &)
{

}

glm::vec2 WComponent::globalPos() const
{
    glm::vec2 p = pos;
    if(parent)
        p += parent->globalPos();

    switch (anchor) {
        case ANCHOR_TOP_RIGHT:
            if(parent)
                p += glm::vec2(parent->size.x, parent->header);
            return p;

        case ANCHOR_TOP_LEFT:
            if(parent)
                p += glm::vec2(0, parent->header);
            return p;

        case ANCHOR_DOWN_RIGHT:
            if(parent)
                p += parent->size;
            return p;

        case ANCHOR_DOWN_LEFT:
            if(parent)
                p += glm::vec2(0, parent->size.y);
            return p;

        case ANCHOR_CENTER:
            return parent->globalPos() + glm::vec2(0, parent->header) - size / 2.f + (parent->size - glm::vec2(0, parent->header)) / 2.f + pos;

        case ANCHOR_CENTER_HOR:
            return parent->globalPos() - glm::vec2(0, parent->header) - glm::vec2(size.x, 0) / 2.f + glm::vec2(parent->size.x, 0) / 2.f + pos;

        default: //ANCHOR_NO
            return pos;
    }
}


WContainer::WContainer(WContainer *par) :
    WComponent(par)
{

}

WContainer::~WContainer()
{

}

void WContainer::Draw() const
{
    WinS::sb->reduceScissor(globalPos() + glm::vec2(0,header), size - glm::vec2(0,header));
    for(auto &i : Items)
    {
        if(i->hidden) continue;

        i->Draw();
    }
    WComponent::Draw();
}

void WContainer::Update(const GameTimer &gt, const MouseState &ms)
{
    mouse_hook = false;
    for(auto &i : Items)
    {
        if(i->hidden) continue;

        i->Update(gt, ms);

        if(!mouse_hook && sge::inLimsVec2(Mouse::getCursorPos(), i->globalPos(), i->globalPos() + i->size))
        {
            i->aimed = true;

            if(ms.once_l == ST_ON)
                i->onMouseClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_LEFT, gt.current});
            if(ms.double_l == ST_ON)
                i->onMouseDoubleClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_LEFT, gt.current});
            if(ms.triple_l == ST_ON)
                i->onMouseTripleClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_LEFT, gt.current});

            if(ms.once_r == ST_ON)
                i->onMouseClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_RIGHT, gt.current});
            if(ms.double_r == ST_ON)
                i->onMouseDoubleClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_RIGHT, gt.current});
            if(ms.triple_r == ST_ON)
                i->onMouseTripleClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_RIGHT, gt.current});

            if(ms.once_m == ST_ON)
                i->onMouseClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_MIDDLE, gt.current});
            if(ms.double_m == ST_ON)
                i->onMouseDoubleClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_MIDDLE, gt.current});
            if(ms.triple_m == ST_ON)
                i->onMouseTripleClick({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_MIDDLE, gt.current});

            if(ms.down_l == ST_ON)
                i->onMouseDown({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_LEFT, gt.current});
            if(ms.down_r == ST_ON)
                i->onMouseDown({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_RIGHT, gt.current});
            if(ms.down_m == ST_ON)
                i->onMouseDown({Mouse::getCursorPos(), GLFW_MOUSE_BUTTON_MIDDLE, gt.current});
        }
        else
            i->aimed = false;
    }
    WComponent::Update(gt, ms);
}
