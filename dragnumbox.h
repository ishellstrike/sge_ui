/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef DRAGNUMBOX_H
#define DRAGNUMBOX_H
#include "wins.h"

class DragNumbox : public WComponent
{
public:
    enum {
        LINEAR,
        EXPONENTIAL
    } g_type = LINEAR;

    enum {
        UNLIMITED,
        LIMITED
    } lim_type = LIMITED;

    DragNumbox(WContainer *par);

    void Draw() const override;
    void Update(const GameTimer &gt, const MouseState &ms) override;

    float value = 1.0f;
    float growth = 0.1f;
    float min = 0, max = 100;
    bool in_progress = false;
};

#endif // DRAGNUMBOX_H
