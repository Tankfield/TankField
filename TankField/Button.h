#ifndef _Button_H
#define _Button_H

#include "Object.h"
#include "Mouse.h"

class Button : public Object{
private:
	bool pressed;

public:	
	Button(SDL_Surface* screen, char* texutre, Vector2D position);
	
	virtual void render();
	virtual void onCollision(Object* object);
	bool isPressed();
	void setPressed(bool status);
};


#endif