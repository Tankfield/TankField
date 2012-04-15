#include "Animation.h"

Animation::Animation(){
	currentFrame = 0;
	maxFrames = 0;
	frameInc = 1;
	frameRate = 100;
	oldTime = 0;
	oscillate = false;
}

void Animation::Animate(){
	if(oldTime + frameRate > SDL_GetTicks()){
		return;
	}

	oldTime = SDL_GetTicks();

	currentFrame +=frameInc;

	if(oscillate){
		if(frameInc > 0){
			if(currentFrame >= maxFrames){
				frameInc = -frameInc;
			}
		}else{
			if(currentFrame <= 0){
				frameInc = -frameInc;
			}
		}
	}else{
		if(currentFrame >= maxFrames){
			currentFrame = 0;
		}
	}
}

void Animation::setFrameRate(int rate){
	frameRate = rate;
}

void Animation::setCurrentFrame(int frame){
	if(frame < 0 || frame >=maxFrames){
		return;
	}
	currentFrame = frame;
}

int Animation::getCurrentFrame(){
	return currentFrame;
}







