#ifndef _Missile_H
#define _Missile_H

#include "Object.h"

class Missile : public Object{
public:

	Missile(Texture* texture);

	virtual void update();
	virtual void redner();
};


#endif