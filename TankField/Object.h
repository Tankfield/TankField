#ifndef _Object_H
#define _Object_H
#include "Texture.h"


class Object{
	
	float x, y;

public:
	Object(Texture *texture);
	//~Object();
	Texture *texture;

	float getX() const;
	float getY() const;
	void moveLeft();
	void moveRight();
	void render();
};


#endif