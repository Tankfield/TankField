#ifndef _Object_H
#define _Object_H
#include "Texture.h"
#include "Vector2D.h"


class Object{


public:

	Vector2D position;
	float speed;
	Object(Texture *texture);
	//~Object();
	Texture *texture;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void render();

};


#endif