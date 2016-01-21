#include "table.h"
#include "helper.h"
#include "wins.h"

Table::Table(WContainer *par) :
    WComponent(par)
{

}

Table::~Table()
{

}

void Table::Init(int count)
{
    if(m_count != 0)
        throw std::logic_error(sge::string_format("width already initialized (%d)", m_count));
    m_count = count;
    columns.resize(count);
    for(int i = 0; i < count; i++)
        columns[i].width = 1.f/float(count);
}

void Table::AddRow(const std::vector<boost::any> &row)
{
    if(row.size() != m_count)
        throw std::logic_error(sge::string_format("row width (%d) not equals table width (%d)", row.size(), m_count));

    table.push_back(row);
    sorted = false;
}

void Table::Clear()
{
    table.clear();
}

void Table::SortBy(int by, bool noreverse)
{
    if(sort_by == by && !noreverse)
        reverse_sort = !reverse_sort;

    sort_by = by;
    if(!reverse_sort)
        std::sort(std::begin(table), std::end(table), [&](const std::vector<boost::any> &a, const std::vector<boost::any> &b) -> bool
        {
            if(a[by].type() != b[by].type())
                return false;

            if(a[by].type() == boost::typeindex::type_id<int>().type_info())
                return boost::any_cast<int>(a[by]) < boost::any_cast<int>(b[by]);

            if(a[by].type() == boost::typeindex::type_id<float>().type_info())
                return boost::any_cast<float>(a[by]) < boost::any_cast<float>(b[by]);

            if(a[by].type() == boost::typeindex::type_id<const char *>().type_info())
                return std::string(boost::any_cast<const char *>(a[by])) < std::string(boost::any_cast<const char *>(b[by]));

            return false;
        });
    else
        std::sort(std::begin(table), std::end(table), [&](const std::vector<boost::any> &a, const std::vector<boost::any> &b) -> bool
        {
            if(a[by].type() != b[by].type())
                return false;

            if(a[by].type() == boost::typeindex::type_id<int>().type_info())
                return boost::any_cast<int>(a[by]) > boost::any_cast<int>(b[by]);

            if(a[by].type() == boost::typeindex::type_id<float>().type_info())
                return boost::any_cast<float>(a[by]) > boost::any_cast<float>(b[by]);

            if(a[by].type() == boost::typeindex::type_id<const char *>().type_info())
                return std::string(boost::any_cast<const char *>(a[by])) > std::string(boost::any_cast<const char *>(b[by]));

            return false;
        });

    sorted = true;
}

void Table::Draw() const
{   
    glm::vec2 p = globalPos();
    SpriteBatch &sb = *WinS::sb;

    int size_without_abs = size.x;
    for(int i = 0; i < m_count; ++i)
        size_without_abs -= columns[i].abs_width;

    int x_off = 0;
    for(int i = 0; i < m_count; ++i)
    {
        if(i == sort_by)
            sb.drawText(columns[i].name + (reverse_sort ? " (v)" : " (^)"), p + glm::vec2(x_off, 2), WinS::f, WinS::color.border_up);
        else
            sb.drawText(columns[i].name, p + glm::vec2(x_off, 2), WinS::f, WinS::color.border_up);
        sb.drawLine(p + glm::vec2(x_off, 0), p + glm::vec2(x_off, size.y), 2, WinS::color.border_up);
        x_off += size_without_abs * columns[i].width + columns[i].abs_width;
    }

    int y_off = 20;
    for(int j = 0; j < table.size(); ++j)
    {
        int x_off = 0;
        for(int i = 0; i < m_count; ++i)
        {
            const boost::any &a = table[j][i];
            std::string res;

            if(a.type() == boost::typeindex::type_id<int>().type_info())
                res = sge::string_format("%d", boost::any_cast<int>(a));
            else if(a.type() == boost::typeindex::type_id<float>().type_info())
                res = sge::string_format("%d", boost::any_cast<float>(a));
            else if(a.type() == boost::typeindex::type_id<const char *>().type_info())
                res = boost::any_cast<const char *>(a);
            else res = a.type().name();

            sb.drawText(res, p + glm::vec2(x_off, y_off), WinS::f, hovered == j || selected == j ?
                                                                   WinS::color.hovered_text : WinS::color.text);
            x_off += size_without_abs * columns[i].width + columns[i].abs_width;
        }
        y_off += 20;
    }
    WComponent::Draw();
}

void Table::Update(const GameTimer &gt, const MouseState &ms)
{
    hovered = -1;
    if(aimed)
    {
        hovered = glm::trunc((Mouse::getCursorPos().y - globalPos().y) / 20.f) - 1;
        if(Mouse::isLeftJustPressed())
        {
            selected = hovered;
            int size_without_abs = size.x;
            for(int i = 0; i < m_count; ++i)
                size_without_abs -= columns[i].abs_width;

            int sel = 0;
            int offx = 0, lastx = 0;
            float cpos = Mouse::getCursorPos().x - globalPos().x;
            if(hovered == -1)
            {
                for(int i = 0; i < m_count; ++i)
                {
                    lastx = offx;
                    offx += size_without_abs * columns[i].width + columns[i].abs_width;

                    if(cpos > lastx && cpos < offx)
                    {
                        sel = i;
                        break;
                    }
                }

                SortBy(sel);
            }
        }
    }

    if(!sorted)
        SortBy(sort_by, true);

    WComponent::Update(gt, ms);
}


Column::Column()
{

}

Column::Column(std::string s, float f, int i) : name(s), width(f), abs_width(i)
{

}
