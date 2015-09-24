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
#include <core/tree.h>
#include "spritebatch.h"

class TreeView : public WContainer
{
public:
    TreeView(WContainer *par);
    ~TreeView();

    Tree<WComponent> tree;

    void Draw() const override;
    void Update(const GameTimer &gt, const MouseState &ms) override;
    std::string text;
private:
    void wide(const Tree<WComponent>::root_type root, SpriteBatch &sb, int x, int y, bool from_sister) const;
};

#endif // TREEVIEW_H

