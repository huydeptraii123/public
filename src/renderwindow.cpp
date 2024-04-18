#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_Filepath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_Filepath);
	if (texture == NULL)
	{
		std::cout << "Failed to load a texture. Error: " << SDL_GetError() << std::endl;
	}
	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * 4;
	dst.y = p_entity.getY() * 4;
	dst.w = p_entity.getCurrentFrame().w ;
	dst.h = p_entity.getCurrentFrame().h ;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);

}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
SDL_Window* RenderWindow::getSDLWindow() 
{
    return window;
}
SDL_Texture* RenderWindow::LoadaniTexture(const char *path)
{
	SDL_Surface * tmpSur;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderWindow::renderer,tmpSur);
	SDL_FreeSurface(tmpSur);
	return texture;
}
void RenderWindow::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopyEx(RenderWindow::renderer, tex, &src, &dest, NULL, NULL);
}