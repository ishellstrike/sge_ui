/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef TABLE_H
#define TABLE_H
#include "component.h"
#include <glm/glm.hpp>
#include "spritebatch.h"
#include "boost/any.hpp"

class Column
{
public:
    Column();
    Column(std::string s, float f, int i);

    std::string name;
    float width = 0;
    int abs_width = 0;
};

class Table : public WComponent
{
public:
    Table(WContainer *par);
    ~Table();

    void text(const std::string &__s);
    void align(const SpriteBatch::ALIGN __a);
    const std::string text() const;
    void append(const std::string &__s);

    void Init(int count);
    void AddRow(const std::vector<boost::any> &row);
    void Clear();
    std::vector<std::vector<boost::any>> table;
    std::vector<Column> columns;
    void SortBy(int by, bool noreverse = false);

    void Draw() const override;
    void Update(const GameTimer& gt, const MouseState &ms) override;
    int hovered = -1;
    int selected = 0;
private:
    std::string m_text;
    SpriteBatch::ALIGN m_align = SpriteBatch::ALIGN_LEFT;
    int m_count = 0;
    bool sorted = false;
    int sort_by = 0;
    bool reverse_sort = true;
};

#endif // TABLE_H
