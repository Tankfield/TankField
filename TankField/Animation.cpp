#include "Animation.h"

Animation::Animation(const char* filename, SDL_Surface *screen, unsigned int tilesX, unsigned int tilesY, unsigned int frameRate)
: Texture(filename, screen), currentFrame(1), frameTime(1.0f / frameRate), frameTimeLeft(frameTime), maxFrame(tilesX * tilesY)
{
	this->tilesX = tilesX;
	this->tilesY = tilesY;
	this->frameRate = frameRate;
}

void Animation::update(){
	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;
	
	frameTimeLeft -= timeSinceLastTime;

	if (frameTimeLeft <= 0.0f){
		if (currentFrame == maxFrame){
			currentFrame = 1;
		}else{
			currentFrame++;
		}
		frameTimeLeft = frameTime;
	}

	lastTime = SDL_GetTicks() / 1000.0f;
}

void Animation::drawTexture(int x, int y){
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_Rect frameRect;
	frameRect.x = currentFrame % tilesX * width / tilesX;
	frameRect.y = (currentFrame / tilesX - 1) * height / tilesY;
	frameRect.w = width / tilesX;
	frameRect.h = height / tilesY;

	SDL_BlitSurface(surface, &frameRect, displaySurface, &destRect);
}