#include "win.h"
#include <glm/glm.hpp>
#include "wins.h"
#include "../mouse.h"
#include <vector>
#include "../colorextender.h"
#include "../helper.h"
#include "../prefecences.h"

Win::Win(WContainer *par) :
    WContainer(par)
{
    closeb = new Button(this);
    closeb->text = "X";
    closeb->size = {20,20};
    closeb->anchor = ANCHOR_TOP_RIGHT;
    closeb->pos = {-20, -20};
    closeb->onLeftPress = [&](){hidden = true;};
    header = 20;

    size = {200,200};
}

Win::~Win()
{
}

void Win::Draw() const
{
    SpriteBatch& sb = *WinS::sb;
    //WinS *ws = WinS::ws;

    sb.drawRect(pos, size, WinS::color.basic);

    sb.drawLine(pos + glm::vec2(0, header), glm::vec2(pos.x + size.x, pos.y + header), 2, Color::White);

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    sb.drawText(text, {pos.x + 5, pos.y}, WinS::f, WinS::color.text);

    if(!closeb->hidden) closeb->Draw();

    WContainer::Draw();
}

void Win::Update(const GameTimer &gt)
{
    glm::vec2 wpos = globalPos();
    if(!WinS::MouseHooked && inLimsVec2(Mouse::getCursorLastPos(), wpos, wpos + glm::vec2(size.x - 20, header)))
    {
        if(Mouse::isLeftPressed())
        {
            drag_point = Mouse::getCursorLastPos() - pos;
            dragged = true;
        }
    }
    if(Mouse::isLeftDown() && dragged)
        pos = glm::vec2(Mouse::getCursorPos().x, Mouse::getCursorLastPos().y) - drag_point;
    else
        dragged = false;

    if(!WinS::MouseHooked && inLimsVec2(Mouse::getCursorLastPos(), wpos + glm::vec2(size.x - 10, size.y - 10), wpos + size))
    {
        Mouse::state = Mouse::STATE_RESIZE;
        if(Mouse::isLeftPressed())
        {
            resize_point = Mouse::getCursorLastPos() - size;
            resizing = true;
        }
    }
    if(Mouse::isLeftDown() && resizing)
    {
        size = glm::vec2(Mouse::getCursorPos().x, Mouse::getCursorLastPos().y) - resize_point;
        if(size.y < 40) {
            size.y = 40;
        }
        if(size.x < 100) {
            size.x = 100;
        }
        if(onResize) {
            onResize();
        }
    }
    else
        resizing = false;

    if(!WinS::MouseHooked && inLimsVec2(Mouse::getCursorLastPos(), wpos, wpos + size) && !hidden)
    {
        if(Mouse::isLeftDown())
        {
            WinS::ws->ToTop(this);
        }
        WinS::MouseHooked = true;
    }

    WContainer::Update(gt);
}

void Win::MoveUnderCur()
{
    pos = Mouse::getCursorPos();
    if(pos.x + size.x > RESX)
    {
        pos.x = RESX - size.x;
    }
    if(pos.y + size.y > RESY)
    {
        pos.y = RESY - size.y;
    }
}
