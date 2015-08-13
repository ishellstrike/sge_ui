#ifndef WinS_h__
#define WinS_h__
#include "../spritebatch.h"
#include "../resources/texture.h"
#include <vector>
#include "win.h"
#include <list>
#include <glm/glm.hpp>
#include "../font.h"
#include "../colorscheme.h"
#include "gametimer.h"

#define DRAW_BOX(sb, pos, size, inverted) \
sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, !inverted ? WinS::color.border_up : WinS::color.border_down); \
sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, !inverted ? WinS::color.border_up : WinS::color.border_down); \
sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, !inverted ? WinS::color.border_down : WinS::color.border_up); \
sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, !inverted ? WinS::color.border_down : WinS::color.border_up);

class WinS : public WContainer{
public:
    WinS();
    WinS(SpriteBatch* sb_);
    ~WinS();
    static bool MouseHooked;
    static bool KeyboardHooked;
    static ColorScheme color;

    void Update(const GameTimer &gt);
    void ToTop(WComponent *w);
    void CloseTop();
    std::weak_ptr<WComponent> getInpos(glm::vec2 p);
    static SpriteBatch *sb;
    static Font *f;
    static WinS *ws;
    void Draw() const;
};

#endif // WinS_h__
