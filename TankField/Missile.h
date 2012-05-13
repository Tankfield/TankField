#ifndef _Missile_H
#define _Missile_H

#include "Object.h"

class Missile : public Object{


public:

	Missile(Texture* texture, Vector2D vel, Vector2D pos);	

	virtual void update();
	virtual void render();
};


#endif