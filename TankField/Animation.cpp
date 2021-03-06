#include "Animation.h"

Animation::Animation(const char* filename, SDL_Surface *screen, unsigned int tilesX, unsigned int tilesY, unsigned int frameRate)
: Texture(filename, screen), currentFrame(0), frameTime(1.0f / frameRate), frameTimeLeft(frameTime), maxFrame(tilesX * tilesY), isBackward(false), stopped(true)
{
	this->tilesX = tilesX;
	this->tilesY = tilesY;
	this->frameRate = frameRate;
}

void Animation::update(float timeSinceLastTime){
	
	frameTimeLeft -= timeSinceLastTime;

	if (!stopped) {
		if (frameTimeLeft <= 0.0f){
			if (!isBackward) {
				if (currentFrame == maxFrame - 1){
					currentFrame = 0;
				}else{
					currentFrame++;
				}
			}
			else {
				if (currentFrame == 0){
					currentFrame = maxFrame-1;
				}else{
					currentFrame--;
				}
			}
			frameTimeLeft = frameTime;
		}
	}
}

void Animation::draw(int x, int y){
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_Rect frameRect = getBounds();

	SDL_BlitSurface(surface, &frameRect, displaySurface, &destRect);
}

void Animation::runForward() {
	stopped = false;
	isBackward = false;
}

void Animation::runBackward() {
	stopped = false;
	isBackward = true;
}

void Animation::stop() {
	stopped = true;
}

SDL_Rect Animation::getBounds()
{
	SDL_Rect bounds;

	bounds.w = width / tilesX;
	bounds.h = height / tilesY;
	bounds.x = currentFrame % tilesX * bounds.w;
	bounds.y = currentFrame / tilesX * bounds.h;	

	return bounds;
}