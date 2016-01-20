/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#pragma once
#ifndef WComponent_h__
#define WComponent_h__
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "wcontainer.h"
#include <functional>
#include "../colorextender.h"
#include "gametimer.h"
#include "mouse.h"
#include "core/serialize.h"

#include <boost/signals2.hpp>
#include <boost/any.hpp>
using namespace boost::signals2;

enum ST {
    ST_OFF,
    ST_ON,
    ST_PAST
};

struct MouseState {
    ST once_l;
    ST once_r;
    ST once_m;
    ST double_l;
    ST double_r;
    ST double_m;
    ST triple_l;
    ST triple_r;
    ST triple_m;
    ST down_l;
    ST down_r;
    ST down_m;

    glm::vec2 pos;
    glm::vec2 lpos;
};

class WContainer;
class WComponent {
public:
    enum ANCHOR
    {
        ANCHOR_TOP_LEFT,
        ANCHOR_TOP_RIGHT,
        ANCHOR_DOWN_LEFT,
        ANCHOR_DOWN_RIGHT,
        ANCHOR_CENTER,
        ANCHOR_CENTER_HOR,
        ANCHOR_NO
    };

    WComponent(WContainer *par = nullptr);
    virtual ~WComponent();
    virtual void Draw() const = 0;
    virtual void Update(const GameTimer&, const MouseState &) = 0;
    glm::vec2 globalPos() const;
    WContainer *parent;

    glm::vec2 pos = glm::vec2(0);
    glm::vec2 size = glm::vec2(100);
    std::weak_ptr<WComponent> weak_this;

    ANCHOR anchor = ANCHOR_TOP_LEFT;
    std::string wcomponent_type = "error";

    signal<bool(const ClickHandler &)> onMouseDown;
    signal<bool(const ClickHandler &)> onMouseUp;
    signal<bool(const ClickHandler &)> onMouseClick;
    signal<bool(const ClickHandler &)> onMouseDoubleClick;
    signal<bool(const ClickHandler &)> onMouseTripleClick;
    signal<void()> onWheelUp, onWheelDown;

    bool hidden = false;
    bool aimed = false;
    float header = 0;
    boost::any tag;

    virtual void Deserialize(const rapidjson::Value &val);
};

class WContainer : public WComponent {
    friend class WComponent;
    friend class WinS;
public:
    WContainer(WContainer *par = nullptr);
    virtual ~WContainer();

    virtual void Draw() const;
    virtual void Update(const GameTimer& gt, const MouseState &ms);

    virtual void Deserialize(const rapidjson::Value &val);

protected:
    std::vector<std::shared_ptr<WComponent>> Items;
    bool mouse_hook = false;
};
#endif // WComponent_h__
