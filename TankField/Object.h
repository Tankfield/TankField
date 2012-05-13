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

protected:
	Vector2D position;
	Vector2D velocity;
	float speed;
	Texture *texture;

public:
	Object(Texture *texture);
	~Object();
	
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void stop();

	virtual void update();
	virtual void render();

	float getPositionX();
	float getPositionY();
	float getVelocityX();
	float getVelocityY();

	void setPositionX(float x);
	void setPositionY(float y);
	void setVelocityX(float x);
	void setVelocityY(float y);

	Texture *getTexture();

	static void updateAll();
	static void renderAll();
	static void deleteAll();
};


#endif