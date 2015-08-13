#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "wins.h"

class Connector : public WComponent
{
public:
    Connector(WContainer *par);

    std::weak_ptr<WContainer> linked;
    glm::vec4 color = Color::White;
    void Draw() const;
    void Update(const GameTimer &gt);

    bool in_progress = false;
};

#endif // CONNECTOR_H
