#include "Missile.h"

Missile::Missile(Texture* texture, Vector2D vel, Vector2D pos) : Object(texture){
	position = pos;
	velocity = vel * 500;
}

//int wind = -300;
//int gravity = 700;
//int koef = 1000; //koeficient
//TODO
void Missile::update(float timeSinceLastTime){

	if (this->outOfScreen()){
		dead = true;
		return;
	}

	static bool falling = false;
	
	position += velocity * timeSinceLastTime;
	velocity += Vector2D(0, 700) * timeSinceLastTime;

}

void Missile::render(){
   	this->texture->draw((int)this->position.x,(int)this->position.y);
}