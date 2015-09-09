/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "wins.h"
#include "mouse.h"

class BaseConnector
{
public:
    std::string connector_type = "float";
};

template <typename _Ty = float>
class Connector : public WComponent, public BaseConnector
{
public:

    Connector(WContainer *par) : WComponent(par)
    {
        wcomponent_type = "Connector";
        size = {20,20};
        connector_type = typeid(_Ty).name();
    }

    std::weak_ptr<Connector<_Ty>> linked;
    _Ty linked_value;
    glm::vec4 color = Color::White;
    std::string name;
    bool passive = true;

    void Draw() const override
    {
        SpriteBatch &sb = *WinS::ws->sb;
        auto pos = globalPos();
        auto mpos = Mouse::getCursorPos();
        DRAW_BOX(sb, pos, size, false);

        sb.drawText(name, pos - glm::vec2{0,20}, WinS::f, Color::White);

        sb.resetScissor();
        if(in_progress)
        {
            sb.drawLine(pos + size/2.f, mpos, 2, Color::White);
        }

        if(!linked.expired())
        {
            auto &c = linked.lock();
            auto l_pos = c->globalPos();
            sb.drawLine(pos + size/2.f, l_pos + c->size/2.f, 2, Color::White);
        }

        WComponent::Draw();
    }

    void Update(const GameTimer &gt) override
    {
        if(Mouse::isLeftDown() && aimed)
            in_progress = true;

        if(Mouse::isLeftUp() && !aimed)
        {
            if(in_progress)
            {
                auto mpos = Mouse::getCursorPos();
                auto el = WinS::ws->getInpos(mpos);
                if( !el.expired() && el.lock()->wcomponent_type == "Connector" )
                {
                    auto el_shared = std::dynamic_pointer_cast<BaseConnector>(el.lock());
                    if(el_shared->connector_type == connector_type)
                    {
                        auto el_con = std::dynamic_pointer_cast<Connector<_Ty>>(el.lock());
                        if(el_con.get() != this && el_con->passive != passive)
                        {
                            if(!el_con->linked.expired())
                            {
                                el_con->linked.lock()->linked.reset();
                            }
                            if(!linked.expired())
                            {
                                linked.lock()->linked.reset();
                            }
                            linked = el_con;
                            el_con->linked = std::dynamic_pointer_cast<Connector<_Ty>>(weak_this.lock());
                        }
                    }
                }
                in_progress = false;
            }
        }

        //TODO:dont work
        if(hidden && !linked.expired())
        {
            linked.lock()->linked.reset();
            linked.reset();
        }

        if(passive && !linked.expired())
        {
            linked_value = linked.lock()->linked_value;
        }

        WComponent::Update(gt);
    }

    bool in_progress = false;
};

#endif // CONNECTOR_H
