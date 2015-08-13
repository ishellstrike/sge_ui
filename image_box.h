#ifndef IMAGE_BOX_H
#define IMAGE_BOX_H
#include "wins.h"

class ImageBox : public WComponent
{
public:
    ImageBox(WContainer *par);

    std::shared_ptr<Texture> tex;
    glm::vec4 color = Color::White;
    void Draw() const;
    void Update(const GameTimer &gt);
};

#endif // IMAGE_BOX_H
