#ifndef DRAGNUMBOX_H
#define DRAGNUMBOX_H
#include "wins.h"

class DragNumbox : public WComponent
{
public:
    enum {
        LINEAR,
        EXPONENTIAL
    } g_type = LINEAR;

    enum {
        UNLIMITED,
        LIMITED
    } lim_type = LIMITED;

    DragNumbox(WContainer *par);

    void Draw() const;
    void Update(const GameTimer &gt);

    float value = 1.0f;
    float growth = 0.1f;
    float min = 0, max = 100;
    bool in_progress = false;
};

#endif // DRAGNUMBOX_H
