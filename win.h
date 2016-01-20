/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef Win_h__
#define Win_h__
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include <boost/signals2.hpp>
#include "button.h"
#include "component.h"

class Win : public WContainer
{
public:
    Win(WContainer *par);
    virtual ~Win();
    void Draw() const override;
    void Update(const GameTimer& gt, const MouseState &ms) override;
    glm::vec2 drag_point;
    bool dragged = false;
    bool resizing = false;
    glm::vec2 resize_point;
    void MoveUnderCur();
    boost::signals2::signal<void()> onResize;

    bool movable = false;
    bool resizable = false;

    std::string text;

    Button *closeb;
};

#endif // Win_h__

