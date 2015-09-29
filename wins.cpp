/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/
#include "wins.h"
#include <vector>
#include <list>
#include "../mouse.h"
#include <string>
#include <memory>
#include <algorithm>
#include "../prefecences.h"
#include "helper.h"

WinS::WinS() :
    WContainer()
{
    color = ColorScheme::Basic();
}

WinS::WinS(SpriteBatch *sb_) :
    WContainer()
{
    WinS::sb = sb_;
    color = ColorScheme::Basic();
    ws = this;
}

WinS::~WinS()
{
    Items.clear();
}

void WinS::Draw() const
{
    for(auto &i : Items) {
        if(!i->hidden) {
            i->Draw();
        }
        WinS::sb->resetScissor();
    }
}

void WinS::ToTop(WComponent* w) {
    bool b = false;
    int i = 0;
    decltype(Items.end()) last_e = --Items.end();
    for (auto iter = Items.begin(); iter != last_e; ++iter) {
        if(iter->get() == w || b) {
            std::swap(Items[i], Items[i+1]);
            b = true;
        }
        i++;
    }
}

void WinS::CloseTop()
{
    for (auto iter = Items.begin(); iter != Items.end(); ++iter) {
        Win *w = static_cast<Win*>(iter->get());
        if(!w->closeb->hidden && !w->hidden) {
            w->hidden = true;
            return;
        }
    }
    return;
}

std::weak_ptr<WComponent> WinS::getInpos(glm::vec2 p)
{
    for (auto &iter = Items.rbegin(); iter != Items.rend(); ++iter)
    {
        Win *w = static_cast<Win*>(iter->get());
        for (auto &iter2 = w->Items.begin(); iter2 != w->Items.end(); ++iter2)
        {
            if (sge::inLimsVec2(p, (*iter2)->globalPos(), (*iter2)->globalPos() + (*iter2)->size))
                return (*iter2);
        }
    }
    return std::weak_ptr<WComponent>();
}

#define CLICKS_UPDATE(once_l, double_l, triple_l, last_l, click)                                                               \
if(click)                                                                                                              \
{                                                                                                                      \
    if(once_l && gt.current - last_l < Prefecences::Instance()->double_c && double_l == ST_OFF && triple_l == ST_OFF)  \
    {                                                                                                                  \
        double_l = ST_ON;                                                                                              \
        triple_l = ST_OFF;                                                                                             \
        last_l = gt.current;                                                                                           \
    }                                                                                                                  \
    else                                                                                                               \
    if(gt.current - last_l < Prefecences::Instance()->double_c && double_l != ST_OFF && triple_l == ST_OFF)            \
    {                                                                                                                  \
        double_l = ST_OFF;                                                                                             \
        triple_l = ST_ON;                                                                                              \
        last_l = gt.current;                                                                                           \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        double_l = triple_l = ST_OFF;                                                                                  \
        last_l = gt.current;                                                                                           \
        once_l = ST_ON;                                                                                                \
    }                                                                                                                  \
}                                                                                                                      \
                                                                                                                       \
if(gt.current - last_l > Prefecences::Instance()->double_c)                                                            \
{                                                                                                                      \
    double_l = triple_l = once_l = ST_OFF;                                                                             \
}

#define CLICKS_PAST(once_l, double_l, triple_l) \
    if(once_l == ST_ON)                         \
        once_l = ST_PAST;                       \
    if(double_l == ST_ON)                       \
        double_l = ST_PAST;                     \
    if(triple_l == ST_ON)                       \
        triple_l = ST_PAST;

void WinS::Update(const GameTimer &gt, const MouseState &ms) {
    MouseHooked = false;

    pos = {0,0};
    size = {RESX, RESY};

    static float last_l = 0, last_r = 0, last_m = 0;

    CLICKS_UPDATE(mstate.once_l, mstate.double_l, mstate.triple_l, last_l, Mouse::isLeftJustPressed());
    CLICKS_UPDATE(mstate.once_r, mstate.double_r, mstate.triple_r, last_r, Mouse::isRightJustPressed());
    CLICKS_UPDATE(mstate.once_m, mstate.double_m, mstate.triple_m, last_m, Mouse::isMiddleJustPressed());

    mstate.down_l = Mouse::isLeftDown() ? ST_ON : ST_OFF;
    mstate.down_r = Mouse::isRightDown() ? ST_ON : ST_OFF;
    mstate.down_m = Mouse::isMiddleDown() ? ST_ON : ST_OFF;

    KeyboardHooked = false;
    if(Items.size() > 0)
        Items[Items.size() - 1]->Update(gt, mstate);
    KeyboardHooked = true; //only top win can read keyboard

    for(int i = Items.size() - 2; i >= 0; --i)
    {
        if(!Items[i]->hidden)
            Items[i]->Update(gt, mstate);
    }

    CLICKS_PAST(mstate.once_l, mstate.double_l, mstate.triple_l);
    CLICKS_PAST(mstate.once_r, mstate.double_r, mstate.triple_r);
    CLICKS_PAST(mstate.once_m, mstate.double_m, mstate.triple_m);
}

#undef CLICKS_PAST
#undef CLICKS_UPDATE

bool WinS::KeyboardHooked = false;
bool WinS::MouseHooked = false;
WinS *WinS::ws;
SpriteBatch *WinS::sb = nullptr;
Font *WinS::f = nullptr;
ColorScheme WinS::color;

