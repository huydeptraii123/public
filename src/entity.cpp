
#include "Entity.hpp"

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
    : x(p_x), y(p_y), tex(p_tex)
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 640;
    currentFrame.h = 480;
    SDL_QueryTexture(p_tex, NULL, NULL, &width, &height);
}

void Entity::setSize(int width, int height) {
    currentFrame.w = width;
    currentFrame.h = height;
}

float Entity::getX()
{
    return x;
}

float Entity::getY()
{
    return y;
}

void Entity::setX(float x)
{
    this->x = x;
}

void Entity::setY(float y)
{
    this->y = y;
}

SDL_Texture* Entity::getTex()
{
    return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
    return currentFrame;
}



Obstacle::Obstacle(float x, float y, SDL_Texture* texture) :
 Entity(x, y, texture) 
 {

 }


