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
            if (inLimsVec2(p, (*iter2)->globalPos(), (*iter2)->globalPos() + (*iter2)->size))
                return (*iter2);
        }
    }
    return std::weak_ptr<WComponent>();
}

void WinS::Update(const GameTimer &gt) {
    MouseHooked = false;

    pos = {0,0};
    size = {RESX, RESY};

    KeyboardHooked = false;
    if(Items.size() > 0)
        Items[Items.size() - 1]->Update(gt);
    KeyboardHooked = true; //only top win can read keyboard

    for (auto i = Items.rbegin(); i != Items.rend(); ++i)
    {
        if(!(*i)->hidden)
            (*i)->Update(gt);
    }
}

bool WinS::KeyboardHooked = false;
bool WinS::MouseHooked = false;
WinS *WinS::ws;
SpriteBatch *WinS::sb = nullptr;
Font *WinS::f = nullptr;
ColorScheme WinS::color;

