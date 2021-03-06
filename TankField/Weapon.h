#ifndef _Weapon_H
#define _Weapon_H

#include "Object.h"
#include "Missile.h"
#include "Texture.h"


class Weapon : public Object{
private:
	int degrees;

public:

	Texture* missileTexture;
	Vector2D missileVelocity;
	
	Weapon(Texture* texture, int weaponDegrees);

	float missileDelay;

	int getDegrees();
	void incDegrees();
	void decDegrees();
	void setDegrees(int deg);

	void fireMissile();

	virtual void update(float timeSinceLastTime);
	virtual void onCollision(Object *object);
	
};


#endif