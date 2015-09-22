/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H
#include "component.h"
#include <glm/glm.hpp>
#include <functional>

class Button : public WComponent
{
public:
    Button(WContainer *par);
    ~Button();

    void Draw() const override;
    void Update(const GameTimer &gt, const MouseState &ms) override;
    std::string text;
};

#endif // BUTTON_H
