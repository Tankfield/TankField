#ifndef _Animation_H
#define _Animation_H

#include <SDL\SDL.h>

class Animation{
private:
	int currentFrame;
	int frameInc;

private:
	int frameRate;
	long oldTime;

public:
	int maxFrames;
	bool oscillate;

	Animation();
	
	void Animate();
	
	void setFrameRate(int rate);

	void setCurrentFrame(int frame);

	int getCurrentFrame();


};

#endif