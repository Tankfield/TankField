#include "Missile.h"

Missile::Missile(Texture* texture) : Object(texture){
	position = Vector2D(100,500);
	velocity = Vector2D(45) * 1000;
}


//int wind = -300;
//int gravity = 700;
//int koef = 1000; //koeficient

void Missile::update(){
	static float lastTime = SDL_GetTicks() / 1000.0f;

	float timeSinceLastTime = (SDL_GetTicks() / 1000.0f) - lastTime;

	static bool falling = false;
	
	position += velocity * timeSinceLastTime;
	velocity += Vector2D(0, 700) * timeSinceLastTime;

	lastTime = SDL_GetTicks() / 1000.0f;

}

void Missile::redner(){
	this->texture->drawTexture((int)this->position.x,(int)this->position.y);
}