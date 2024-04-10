#include "Button.hpp"

Button::Button(float x, float y, SDL_Texture* texture) : Entity(x, y, texture) {}

bool Button::isMouseOver(int mouseX, int mouseY) {
    return (mouseX >= getX() && mouseX <= getX() + getWidth() &&
            mouseY >= getY() && mouseY <= getY() + getHeight());
}
