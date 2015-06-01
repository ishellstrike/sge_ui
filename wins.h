#ifndef WinS_h__
#define WinS_h__
#include "sge/spritebatch.h"
#include "sge/texture.h"
#include <vector>
#include "win.h"
#include <list>
#include <glm/glm.hpp>
#include "sge/font.h"
#include "sge/colorscheme.h"

class WinS : public WContainer{
public:
    WinS();
    WinS(SpriteBatch* sb_);
    ~WinS();
    static bool MouseHooked;
    static bool KeyboardHooked;
    static ColorScheme color;

    void Update();
    void ToTop(WComponent *w);
    void CloseTop();
    static SpriteBatch *sb;
    static Font *f;
    static WinS *ws;
    void Draw() const;
};

#endif // WinS_h__
