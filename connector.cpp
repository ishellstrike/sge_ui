#include "connector.h"
#include "mouse.h"

Connector::Connector(WContainer *par) : WComponent(par)
{
    onLeftDown = [&](){in_progress = true;};
    onLeftUp = [&](){
        auto mpos = Mouse::getCursorPos();
        in_progress = false;
        auto el = WinS::ws->getInpos(mpos);
        if(typeid(el) == typeid(Connector*))
        {
            linked = el.lock();
        }
    };

    pos = {20,20};
}

void Connector::Draw() const
{
    SpriteBatch &sb = *WinS::ws->sb;
    auto pos = globalPos();
    DRAW_BOX(sb, pos, size, false);

    if(!linked.expired())
    {
        auto &c = linked.lock();
        auto l_pos = c->pos;
        sb.drawLine(pos, l_pos, 2, Color::White);
    }

    WComponent::Draw();
}

void Connector::Update(const GameTimer &gt)
{
    WComponent::Update(gt);
}
