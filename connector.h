/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "wins.h"
#include "mouse.h"
#include <glm/gtc/constants.hpp>

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

    glm::vec2 bezier(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d, float k1) const
    {

      float k2 = 1 - k1;

      glm::vec2 bt;
      bt.x = 2.f * b.x - (c.x + a.x) / 2.f;
      bt.y = 2.f * b.y - (c.y + a.y) / 2.f;

      glm::vec2 ct;
      ct.x = 2.f * c.x - (b.x + d.x) / 2.f;
      ct.y = 2.f * c.y - (b.y + d.y) / 2.f;

      float gamma3 = k1*k2;
      float gamma1 = k2*k2*k2 + gamma3;
      float gamma2 = k1*k1*k1 + gamma3;

      glm::vec2 x;
      x.x = b.x * gamma1 + c.x * gamma2 + (bt.x * k2 + ct.x * k1) * gamma3;
      x.y = b.y * gamma1 + c.y * gamma2 + (bt.y * k2 + ct.y * k1) * gamma3;

      return x;
    }

    inline glm::vec2 cosine(glm::vec2 a, glm::vec2 b, float k) const
    {
      glm::vec2 t;
      t.x = ((a.x + b.x) + (a.x - b.x) * glm::cos(glm::pi<float>() * k)) / 2.f;
      t.y = ((a.y + b.y) + (a.y - b.y) * glm::cos(glm::pi<float>() * k)) / 2.f;
      return t;
    }

    void DrawLineParts(glm::vec2 start, glm::vec2 end, int wi, const glm::vec4 &col) const
    {
        SpriteBatch &sb = *WinS::ws->sb;
        auto len = glm::distance(start, end);

        glm::vec2 pre = start;
        for(int i = 1; i<len/5; ++i)
        {
            auto t = bezier(start - glm::vec2(len*2,len*2), start, end, end + glm::vec2(len*2,len*2), i * 1/(len/5));
            sb.drawLine(pre, t, wi, col);
            pre = t;
        }
    }

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
            DrawLineParts(pos + size/2.f, mpos, 2, Color::White);
        }

        if(!linked.expired())
        {
            auto &c = linked.lock();
            auto l_pos = c->globalPos();
            DrawLineParts(pos + size/2.f, l_pos + c->size/2.f, 2, Color::White);
        }

        WComponent::Draw();
    }

    void Update(const GameTimer &gt, const MouseState &ms) override
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

        WComponent::Update(gt, ms);
    }

    bool in_progress = false;
};

#endif // CONNECTOR_H
