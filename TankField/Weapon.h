#ifndef _Weapon_H
#define _Weapon_H

#include "Object.h"
#include "Missile.h"
#include "Texture.h"


class Weapon : public Object{
public:
	Texture* missileTexture;
	Vector2D missileVelocity;
	Weapon(Texture* texture, Vector2D pos);
	Weapon(Texture* texture);

	void fireMissile(Vector2D pos);

};


#endif