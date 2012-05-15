#include "Missile.h"
#include "Tank.h"
#include "Weapon.h"
#include "Globals.h"

Missile::Missile(Texture* texture, Vector2D vel, Vector2D pos) : Object(texture, pos){
	position = pos;
	velocity = vel * MISSILE_FIRE_POWER;
}


void Missile::update(float timeSinceLastTime){

	if (this->outOfScreen()){
		dead = true;
		return;
	}
	
	position += velocity * timeSinceLastTime;
	velocity += Vector2D(wind * WIND_POWER, GRAVITY) * timeSinceLastTime;

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
	if (dynamic_cast<Tank*>(object) != NULL){
		this->dead = true;
	}
	if (dynamic_cast<Tank*>(object) != NULL){
		this->dead = true;
	}

}