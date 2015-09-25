/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/
#include "treeview.h"
#include "wins.h"
#include "../colorextender.h"
#include "../mouse.h"
#include "../helper.h"

#include <sge_ui/label.h>

void add_r(const Tree<WComponent>::root_type root, int x)
{
    if(x <= 0) return;
    for(int i =5;i<rand()%20;i++)
    {
        auto t = new Label(root->data->parent);
        auto tt = root->add_sister(t);
        if(rand()%25 == 1)
            add_r(tt, x - 1);
    }
    auto t = new Label(root->data->parent);
    auto tt = root->add_child(t);
    add_r(tt, x - 1);
}

TreeView::TreeView(WContainer *par) :
    WContainer(par)
{
    auto t = new Label(this);
    auto tt = tree.root->add_child(t);

    add_r(tt, 30);
}

TreeView::~TreeView()
{

}

void TreeView::wide(const Tree<WComponent>::root_type root, SpriteBatch &sb, int x, int y, bool from_sister) const
{
    auto pos = globalPos();

    sb.drawLine(pos + glm::vec2(x - (from_sister ? 0 : 20), y - 20), pos + glm::vec2(x, y), 2, Color::DarkRed);
    //sb.drawText("a", {x, y}, WinS::f, Color::Red);
    if(root->data)
        root->data->pos = {x,y};
    if(root->sister)
    {
        y+=20;
        wide(root->sister, sb, x, y, true);
    }
    if(root->child)
    {
        x+=20;
        y+=20;
        wide(root->child, sb, x, y, false);
    }
    x-=20;
}

void TreeView::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    bool pressed = Mouse::isLeftDown() && aimed;
    DRAW_BOX(sb, pos, size, pressed);


    WContainer::Draw();

    wide(tree.root, sb, 0, 0, false);
}

void TreeView::Update(const GameTimer &gt, const MouseState &ms)
{
    WContainer::Update(gt, ms);
}
