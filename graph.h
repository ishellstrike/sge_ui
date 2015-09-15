/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H
#include "win.h"
#include <vector>
#include <boost/circular_buffer.hpp>

class Graph : public WComponent
{
public:
    Graph(WContainer *par);

    void Draw() const override;
    void Update(const GameTimer &gt) override;
    void AddValue(float a);

    boost::circular_buffer<float> data;
    float min = 0, max = 100;
};

#endif // GRAPH_H
