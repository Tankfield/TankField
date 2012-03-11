#ifndef _Object_H
#define _Object_H
#include "Texture.h"


class Object{
	
	unsigned int x, y;

public:
	Object(Texture *texture);
	//~Object();
	Texture *texture;
};


#endif