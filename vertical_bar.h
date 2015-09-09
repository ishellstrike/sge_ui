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

    float top = 0.1, bot = 0.9;

    void Draw() const override;
    void Update(const GameTimer &gt) override;
};

#endif // VERTICAL_BAR_H
