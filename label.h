/*******************************************************************************
        Copyright (C) 2015 Samsonov Andrey

        This software is distributed freely under the terms of the MIT LICENSE.
        See "LICENSE.txt"
*******************************************************************************/

#ifndef LABEL_H
#define LABEL_H
#include "component.h"
#include <glm/glm.hpp>
#include "spritebatch.h"

class Label : public WComponent
{
public:
    Label(WContainer *par);
    ~Label();

    void text(const std::string &__s);
    void align(const SpriteBatch::ALIGN __a);
    const std::string text() const;
    void append(const std::string &__s);

    void Draw() const override;
    void Update(const GameTimer &gt, const MouseState &ms) override;
private:
    std::string m_text;
    SpriteBatch::ALIGN m_align = SpriteBatch::ALIGN_LEFT;
};

#endif // LABEL_H
