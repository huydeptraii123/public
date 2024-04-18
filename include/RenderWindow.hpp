#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_Filepath);
    void cleanUp();
    void clear();
    void render(Entity& p_entity);
    void display();
    SDL_Window* getSDLWindow();
    SDL_Renderer* getRenderer() const { return renderer; }
    SDL_Texture* LoadaniTexture(const char *path);
    void draw(SDL_Texture* tex, SDL_Rect * srcR, SDL_Rect * destR);
    SDL_Renderer* renderer;
private:
    SDL_Window* window;
    
};
