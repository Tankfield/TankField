#ifndef _Missile_H
#define _Missile_H

#include "Object.h"
#include "Ground.h"
#include "Terrain.h"

class Missile : public Object{

public:

	Missile(Texture* texture, Vector2D vel, Vector2D pos);	

	virtual void update(float timeSinceLastTime);
	virtual void render();

	virtual void onCollision(Object *object);
};


#endif