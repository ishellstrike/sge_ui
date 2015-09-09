/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef Win_h__
#define Win_h__
#include <glm/glm.hpp>
#include "component.h"
#include <vector>
#include <string>
#include <memory>
#include "button.h"

class Win : public WContainer
{
public:
    Win(WContainer *par);
    virtual ~Win();
    void Draw() const override;
    void Update(const GameTimer &gt) override;
    glm::vec2 drag_point;
    bool dragged = false;
    bool resizing = false;
    glm::vec2 resize_point;
    void MoveUnderCur();
    std::function<void()> onResize;

    bool movable = false;
    bool resizable = false;

    std::string text;

    Button *closeb;
};

#endif // Win_h__

