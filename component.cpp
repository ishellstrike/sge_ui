#include "wins.h"
#include "component.h"
#include "../mouse.h"
#include "../helper.h"


WComponent::WComponent(WContainer *par)
{
    parent = par;
    if(parent)
        parent->Items.push_back(std::shared_ptr<WComponent>(this));
}

WComponent::~WComponent()
{

}

void WComponent::Draw() const
{

}

void WComponent::Update(const GameTimer &gt)
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

void WContainer::Update(const GameTimer &gt)
{
    mouse_hook = false;
    for(auto &i : Items)
    {
        if(i->hidden) continue;

        i->Update(gt);

        if(!mouse_hook && inLimsVec2(Mouse::getCursorPos(), i->globalPos(), i->globalPos() + i->size))
        {
            i->aimed = true;
            if(Mouse::isLeftJustPressed() && i->onLeftPress)
            {
                i->onLeftPress();
                mouse_hook = true;
            }
            if(Mouse::isRightJustPressed() && i->onRightPress)
            {
                i->onRightPress();
                mouse_hook = true;
            }

            if(Mouse::isLeftDown() && i->onLeftDown)
            {
                i->onLeftDown();
                mouse_hook = true;
            }
            if(Mouse::isRightDown() && i->onRightDown)
            {
                i->onRightDown();
                mouse_hook = true;
            }
        }
        else
            i->aimed = false;

        if(Mouse::isRightUp() && i->onRightUp)
            i->onRightUp();
        if(Mouse::isLeftUp() && i->onLeftUp)
            i->onLeftUp();
    }
    WComponent::Update(gt);
}
