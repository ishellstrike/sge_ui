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

    void Draw() const;
    void Update();
private:
    std::string m_text;
    SpriteBatch::ALIGN m_align = SpriteBatch::ALIGN_LEFT;
};

#endif // LABEL_H
