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
	
	Weapon(Texture* texture, Vector2D pos);
	Weapon(Texture* texture);

	float missileDelay;
	bool firedMissile;

	int getDegrees();
	void incDegrees();
	void decDegrees();

	void fireMissile();

	virtual void update(float timeSinceLastTime);
	virtual void onCollision(Object *object);
	
};


#endif