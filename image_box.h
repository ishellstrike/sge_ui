/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef IMAGE_BOX_H
#define IMAGE_BOX_H
#include "wins.h"

class ImageBox : public WComponent
{
public:
    ImageBox(WContainer *par);

    std::shared_ptr<Texture> tex;
    glm::vec4 color = Color::White;
    void Draw() const override;
    void Update(const GameTimer& gt, const MouseState &ms) override;
};

#endif // IMAGE_BOX_H
