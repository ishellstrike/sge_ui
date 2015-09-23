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

#include <boost/graph/graph_traits.hpp>
#include <sge_ui/label.h>

TreeView::TreeView(WContainer *par) :
    WContainer(par)
{
    g = std::make_shared<Graph>(1);
    auto v = std::make_shared<Vertex>(g, stored);
    stored.push_back(v);

    auto ll = new Label(this);
    v->add_child(ll);

    ll = new Label(this);
    auto out = v->add_child(ll);

    ll = new Label(this);
    out->add_child(ll);

    ll = new Label(this);
    out->add_child(ll);
}

TreeView::~TreeView()
{

}

void TreeView::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    bool pressed = Mouse::isLeftDown() && aimed;
    DRAW_BOX(sb, pos, size, pressed);

    WinS::sb->drawText(text, pos, size, WinS::f, aimed ? WinS::color.hovered_text : WinS::color.text, SpriteBatch::ALIGN_CENTER);

    typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
    std::pair<vertex_iter, vertex_iter> vp;
    for (vp = boost::vertices(*g); vp.first != vp.second; ++vp.first)
    {
        LOG(info) << *vp.first << " " << *vp.second;
    }

    WComponent::Draw();
}

void TreeView::Update(const GameTimer &gt, const MouseState &ms)
{
    WComponent::Update(gt, ms);
}



TreeView::Vertex::Vertex(std::shared_ptr<TreeView::Graph> &__gr, std::vector<std::shared_ptr<Vertex> > &__stored) : gr(__gr), stored(__stored)
{

}

std::shared_ptr<TreeView::Vertex> TreeView::Vertex::add_child(WComponent *wc)
{
    int post_last = stored.size() - 1;
    auto a = std::make_shared<Vertex>(gr, stored);
    a->store = wc;
    index = post_last;

    stored.push_back(a);
    auto n = boost::add_vertex(*gr);
    boost::add_edge(index, n, *gr);

    return stored[post_last];
}
