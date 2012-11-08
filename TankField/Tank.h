#ifndef _Tank_H
#define _Tank_H
#include "Object.h"
#include "Weapon.h"

class Tank : public Object{

private:
	Vector2D weaponPosition;
	int health;
public:
	Weapon* weapon;
	Tank(Texture* texture, Weapon* weapon, Vector2D tankPos, Vector2D weaponPos);
	
	float getWeaponPositionX();
	float getWeaponPositionY();

	int getHealth();
	void setHealth(int hp);

	bool isDead();

	void fire();

	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void stop();

	virtual void update(float timeSinceLastTime);
	virtual void render();

	virtual void onCollision(Object *object);
};

#endif