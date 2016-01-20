/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef PANEL_H
#define PANEL_H
#include "component.h"

class Panel : public WContainer
{
public:
    Panel(WContainer *par);
    ~Panel();

    void Draw() const override;
    void Update(const GameTimer& gt, const MouseState &ms) override;
};

#endif // PANEL_H
