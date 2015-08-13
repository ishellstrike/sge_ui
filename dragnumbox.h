#ifndef DRAGNUMBOX_H
#define DRAGNUMBOX_H
#include "wins.h"

class DragNumbox : public WComponent
{
public:
    enum GrowthType {
        LINEAR,
        EXPONENTIAL
    } g_type = LINEAR;

    DragNumbox(WContainer *par);

    void Draw() const;
    void Update(const GameTimer &gt);

    float value = 1.0f;
    float growth = 0.1f;
    bool in_progress = false;
};

#endif // DRAGNUMBOX_H
