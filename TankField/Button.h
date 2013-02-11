#ifndef _Button_H
#define _Button_H

#include "Object.h"

class Button : public Object{
private:

public:	
	Button(SDL_Surface* screen, char* texutre, Vector2D position);
	~Button();

	virtual void render();
};


#endif