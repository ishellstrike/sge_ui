#include "sge_ui/wins.h"
#include <vector>
#include <list>
#include "sge/mouse.h"
#include <string>
#include <memory>
#include <algorithm>
#include "sge/prefecences.h"

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

void WinS::Update() {
    MouseHooked = false;

    pos = {0,0};
    size = {RESX, RESY};

    KeyboardHooked = false;
    if(Items.size() > 0)
        Items[Items.size() - 1]->Update();
    KeyboardHooked = true; //only top win can read keyboard

    for (auto i = Items.rbegin(); i != Items.rend(); ++i)
    {
        if(!(*i)->hidden)
            (*i)->Update();
    }
}

bool WinS::KeyboardHooked = false;
bool WinS::MouseHooked = false;
WinS *WinS::ws;
SpriteBatch *WinS::sb = nullptr;
Font *WinS::f = nullptr;
ColorScheme WinS::color;

