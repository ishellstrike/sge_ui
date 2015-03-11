#include "panel.h"
#include "sge/spritebatch.h"
#include "wins.h"
#include "sge/colorextender.h"

Panel::Panel(WContainer *par) :
    WContainer(par)
{

}

Panel::~Panel()
{

}

void Panel::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    WContainer::Draw();
}

void Panel::Update()
{
    WContainer::Update();
}

