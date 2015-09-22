/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#include "helper.h"
#include "graph.h"
#include "../spritebatch.h"
#include "wins.h"
#include "../colorextender.h"
#include <algorithm>

Graph::Graph(WContainer *par) :
    WComponent(par)
{
    data.resize(100);
    size = {100,100};
}

void Graph::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    float x = 1;
    float ysize = size.y * 0.8f;
    auto max = *std::max_element(std::begin(data), std::end(data));
    auto min = *std::min_element(std::begin(data), std::end(data));
    for(auto b = data.begin(); b != data.end(); ++b)
    {
        auto a = b+1;
        if(a == data.end()) a = data.begin();

        auto preval = (1-(((*b)-min) / (max-min)))*ysize;
        auto val = (1-(((*a)-min) / (max-min)))*ysize;

        sb.drawLine(glm::vec2((size.x)/static_cast<float>(data.size()) * (x - 1), preval) + pos,
                    glm::vec2(size.x/static_cast<float>(data.size()) * x, val) + pos, 1, WinS::color.border_up);
        x++;
    }

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    sb.drawText(string_format("%g", max), {pos.x, pos.y + 2}, WinS::f, WinS::color.text);
    sb.drawText(string_format("%g", min), {pos.x, pos.y + size.y - 15}, WinS::f, WinS::color.text);

    WComponent::Draw();
}

void Graph::Update(const GameTimer &gt, const MouseState &ms)
{
    WComponent::Update(gt, ms);
}

void Graph::AddValue(float a)
{
    data.push_back(a);
}

