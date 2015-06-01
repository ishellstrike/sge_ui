#include "vertical_bar.h"
#include "sge/spritebatch.h"
#include "sge/colorextender.h"
#include "wins.h"

VerticalBar::VerticalBar(WContainer* par) :
    WComponent(par)
{

}

VerticalBar::~VerticalBar()
{

}

void VerticalBar::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, aimed ? WinS::color.hovered_text : WinS::color.text);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, aimed ? WinS::color.hovered_text : WinS::color.text);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, aimed ? WinS::color.hovered_text : WinS::color.text);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, aimed ? WinS::color.hovered_text : WinS::color.text);

    float nsize = size.y - 4;
    sb.drawRect(pos + glm::vec2(3) + glm::vec2(0, nsize*top), size - glm::vec2(4) - glm::vec2(0, nsize*top + nsize*(1-bot)), WinS::color.border_up);

    WComponent::Draw();
}

void VerticalBar::Update()
{
    WComponent::Update();
}

