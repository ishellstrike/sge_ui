/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef VERTICAL_BAR_H
#define VERTICAL_BAR_H
#include "component.h"

class VerticalBar : public WComponent
{
public:
    VerticalBar(WContainer *par);
    ~VerticalBar();

    float top = 0.1f, bot = 0.9f;

    void Draw() const override;
    void Update(const GameTimer& gt, const MouseState &ms) override;
};

#endif // VERTICAL_BAR_H
