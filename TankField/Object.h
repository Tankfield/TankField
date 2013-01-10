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

	bool dead;

public:
	Object(Texture *texture, Vector2D position);
	virtual ~Object();
	
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void stop();

	virtual void update(float timeSinceLastTime);
	virtual void render();

	bool outOfScreen();
	bool checkCollision(Object *object);

	virtual void onCollision(Object *object);

	float getPositionX();
	float getPositionY();
	float getVelocityX();
	float getVelocityY();

	void setPositionX(float x);
	void setPositionY(float y);
	void setVelocityX(float x);
	void setVelocityY(float y);

	SDL_Rect getTextureIntersection(SDL_Rect objectIntersection);

	Texture *getTexture();

	static void updateAll(float timeSinceLastTime);
	static void renderAll();
	static void deleteAll();
	static void removeDead();
};


#endif