
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity {
public:
    Entity(float p_x, float p_y, SDL_Texture* p_tex);
    float getX();
    float getY();
    void setX(float x); 

    void setY(float y); 

    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    void setSize(int width, int height);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
    int width, height;
};

class Obstacle : 
public 
Entity 
{
public:
    Obstacle(float x, float y, SDL_Texture* texture);
};

