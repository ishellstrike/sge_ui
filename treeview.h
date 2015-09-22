/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/
#ifndef TREEVIEW_H
#define TREEVIEW_H
#include "component.h"
#include <glm/glm.hpp>
#include <functional>

class TreeView : public WComponent
{
public:
    TreeView(WContainer *par);
    ~TreeView();

    void Draw() const override;
    void Update(const GameTimer &gt, const MouseState &ms) override;
    std::string text;
};

#endif // TREEVIEW_H

