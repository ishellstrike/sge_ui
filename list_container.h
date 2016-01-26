/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef LIST_H
#define LIST_H
#include "component.h"
#include "button.h"
#include "vertical_bar.h"

//BUG: после отрисовки scisor не восстанавливается до предыдущего значения
class ListContainer : public WContainer
{
public:
    ListContainer(WContainer *par);
    ~ListContainer();

    void Draw() const override;
    void Update(const GameTimer& gt, const MouseState &ms) override;

    int top = 0, bot = 0;

    typedef std::shared_ptr<WComponent> WComp_ptr;

    Button *up, *down;
    VerticalBar *bar;
    const int stored_items_offset = 3;

    size_t Count() const;
    void Clear();
private:
    void nolmalze_top_bot();
};

#endif // LIST_H
