#ifndef _Weapon_H
#define _Weapon_H

#include "Object.h"

class Weapon : public Object{
public:

	Weapon(Texture* texture, Vector2D pos);
	Weapon(Texture* texture);
	Weapon();

	

};


#endif