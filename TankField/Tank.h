#ifndef _Tank_H
#define _Tank_H
#include "Object.h"
#include "Weapon.h"

class Tank : public Object{
public:
	Weapon* weapon;
	Tank(Texture* texture, Weapon* weapon);
	
	void fire();

	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void stop();

	virtual void update(float timeSinceLastTime);
	virtual void render();
};

#endif