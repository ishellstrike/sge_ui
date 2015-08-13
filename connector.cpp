#include "connector.h"
#include "mouse.h"

Connector::Connector(WContainer *par) : WComponent(par)
{
    type = "Connector";
    size = {20,20};
}

void Connector::Draw() const
{
    SpriteBatch &sb = *WinS::ws->sb;
    auto pos = globalPos();
    auto mpos = Mouse::getCursorPos();
    DRAW_BOX(sb, pos, size, false);

    sb.resetScissor();
    if(in_progress)
    {
        sb.drawLine(pos + size/2.f, mpos, 2, Color::White);
    }

    if(!linked.expired())
    {
        auto &c = linked.lock();
        auto l_pos = c->globalPos();
        sb.drawLine(pos + size/2.f, l_pos + c->size/2.f, 2, Color::White);
    }

    WComponent::Draw();
}

void Connector::Update(const GameTimer &gt)
{
    if(Mouse::isLeftDown() && aimed)
        in_progress = true;

    if(Mouse::isLeftUp() && !aimed)
    {
        if(in_progress)
        {
            auto mpos = Mouse::getCursorPos();
            auto el = WinS::ws->getInpos(mpos);
            if( !el.expired() && el.lock()->type == "Connector" )
            {
                if(el.lock().get() != this)
                {
                    linked = el.lock();
                }
            }
            in_progress = false;
        }
    }

    WComponent::Update(gt);
}
