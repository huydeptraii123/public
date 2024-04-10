#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Entity.hpp"

class Button : public Entity {
public:
    Button(float x, float y, SDL_Texture* texture);
    bool isMouseOver(int mouseX, int mouseY);
};

#endif // BUTTON_HPP
