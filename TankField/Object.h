#ifndef _Object_H
#define _Object_H
#include <vector>
using std::vector;

#include "Texture.h"
#include "Vector2D.h"
#include "Animation.h"


class Object{
private:
	static vector<Object*> allObjects;

public:	
	Vector2D position;
	Vector2D velocity;
	float speed;
	Texture *texture;


	Object(Texture *texture);
	~Object();
	

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void stop();

	virtual void update();
	virtual void render();

	static void updateAll();
	static void renderAll();
	static void deleteAll();
};


#endif