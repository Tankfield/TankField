#include "Missile.h"

Missile::Missile(Texture* texture, Vector2D vel, Vector2D pos) : Object(texture, pos){
	position = pos;
	velocity = vel * 1000;
}

//int wind = -300;
//int gravity = 700;
//int koef = 1000; //koeficient
void Missile::update(float timeSinceLastTime){

	if (this->outOfScreen()){
		dead = true;
		return;
	}
	
	position += velocity * timeSinceLastTime;
	velocity += Vector2D(0, 700) * timeSinceLastTime;

}

void Missile::render(){
   	this->texture->draw((int)this->position.x,(int)this->position.y);
}

void Missile::onCollision(Object *object) {
	if (dynamic_cast<Missile*>(object) != NULL){
		this->dead = true;
	}
	if (dynamic_cast<Terrain*>(object) != NULL){
		this->dead = true;
	}
	if (dynamic_cast<Ground*>(object) != NULL){
		this->dead = true;
	}


}