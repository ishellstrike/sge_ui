/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#include "list_container.h"
#include "wins.h"
#include "../colorextender.h"
#include "label.h"

void ListContainer::nolmalze_top_bot()
{
    top = glm::clamp(top, 0, (int)ItemsCount() - 1);
    bot = glm::clamp(bot, 0, (int)ItemsCount() + 1);
    if(top > bot){
        std::swap(top, bot);
    }
}

ListContainer::ListContainer(WContainer *par) :
    WContainer(par)
{
    wcomponent_type = "listcontainer";
    //for(int i=0;i<10;i++)
    //{
    //    auto l = new Label(this);
    //    l->text("test"+std::to_string(i));
    //}

    size = {150,100};

    up = new Button(this);
    up->text = "^";
    up->anchor = ANCHOR_TOP_RIGHT;
    up->size = {20,20};
    up->pos = {-20,0};   
    up->onMouseDown.connect( [&](const ClickHandler &mh)->bool{
        static float last = 0;
        if(mh.button == GLFW_MOUSE_BUTTON_LEFT && mh.time - last > 0.1)
        {
            last = mh.time;
            top--;
            nolmalze_top_bot();
            return true;
        }
        return false;
    });

    down = new Button(this);
    down->text = "v";
    down->anchor = ANCHOR_DOWN_RIGHT;
    down->size = {20,20};
    down->pos = {-20,-20};
    down->onMouseDown.connect( [&](const ClickHandler &mh)->bool{
        static float last = 0;
        if(mh.button == GLFW_MOUSE_BUTTON_LEFT && mh.time - last > 0.1)
        {
            last = mh.time;
            top++;
            nolmalze_top_bot();
            return true;
        }
        return false;
    });

    bar = new VerticalBar(this);
    bar->anchor = ANCHOR_TOP_RIGHT;
    bar->pos = {-20, 20};
    bar->size = {20, 20};
    bar->onMouseDown.connect( [&](const ClickHandler &mh)->bool{
        if(mh.button == GLFW_MOUSE_BUTTON_LEFT)
        {
            auto p = mh.pos.y - bar->globalPos().y;
            auto s = bar->size.y;

            top = ItemsCount() * p / s;

            nolmalze_top_bot();
            return true;
        }
        return false;
    });

    onWheelDown.connect( [&]{
        top++;
        nolmalze_top_bot();
    });

    onWheelUp.connect( [&]{
        top--;
        nolmalze_top_bot();
    });
}

ListContainer::~ListContainer()
{

}

void ListContainer::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    std::for_each(Items.begin()+=stored_items_offset, Items.end(), [](const WComp_ptr &iter){ iter->hidden = true; });

    int j = 0;
    bar->top = (top)/(float)(ItemsCount());
    bar->bot = 1.0;
    for(auto i = Items.begin() + stored_items_offset + top; i != Items.end(); ++i, ++j)
    {
        if((j)*20 >= size.y)
        {
            bar->bot = (top+j)/(float)(ItemsCount());
            break;
        }
        (*i)->hidden = false;
        (*i)->pos = glm::vec2(0, j * 20);
    }

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    WContainer::Draw();
}

void ListContainer::Update(const GameTimer &gt, const MouseState &ms)
{
    bar->size.y = size.y - 40;
    WContainer::Update(gt, ms);
}

size_t ListContainer::ItemsCount() const
{
    return Items.size() - stored_items_offset;
}

void ListContainer::ItemsClear()
{
    Items.erase(Items.begin() += stored_items_offset, Items.end());
}
