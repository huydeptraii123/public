#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "defs.h"
#include <vector>

struct Sprite {
	SDL_Texture* texture;
	std::vector<SDL_Rect> clips;
	int currentFrame = 0;

	void init(SDL_Texture* _texture, int frames, const int _clips [] [2] ) {
		texture = _texture;

		SDL_Rect clip;
		for (int i=0; i < frames; i++)
		{
			clip.x = _clips[i][0];
			clip.y = _clips[i][1];
			clip.w = _clips[i][2];
			clip.h = _clips[i][3];
			clips.push_back(clip);
		}
	}
	void tick() {
		currentFrame = (currentFrame + 1) % clips.size();

	}
	const SDL_Rect* getCurrentClip () const {
		return &{clips[currentFrame]};
	}
};