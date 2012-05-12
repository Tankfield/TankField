#ifndef _Tank_H
#define _Tank_H
#include "Object.h"
#include "Weapon.h"

class Tank : public Object{
public:
	Weapon weapon;
	Tank(Texture* texture, Weapon weapon);

	virtual void update();
	virtual void render();
};

#endif