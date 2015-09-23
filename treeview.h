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

#include <boost/graph/adjacency_list.hpp>

class TreeView : public WContainer
{
public:
    TreeView(WContainer *par);
    ~TreeView();

    struct Vertex;

    typedef std::pair<int,int> E;
    typedef boost::adjacency_list<> Graph;

    struct Vertex
    {
        WComponent *store;
        int index = 0;

        std::shared_ptr<Graph> &gr;
        std::vector<std::shared_ptr<Vertex>> &stored;

        Vertex(std::shared_ptr<Graph> &__gr, std::vector<std::shared_ptr<Vertex>> &__stored);
        std::shared_ptr<TreeView::Vertex> add_child(WComponent *wc);
    };

    std::shared_ptr<Graph> g;
    std::vector<std::shared_ptr<Vertex>> stored;

    void Draw() const override;
    void Update(const GameTimer &gt, const MouseState &ms) override;
    std::string text;
};

#endif // TREEVIEW_H

