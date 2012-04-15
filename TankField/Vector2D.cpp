#include <math.h>
#include "Vector2D.h"

Vector2D::Vector2D(){
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2D::Vector2D(float x, float y){
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D(float angle){
	angle *= DEG2RAD; 
	this->x = sin(angle); 
	this->y = -cos(angle);
	
	this->Normalize();
}

float Vector2D::Magnitude(){
	return (sqrt(pow(this->x, 2) + pow(this->y, 2)));
}

void Vector2D::Normalize(){
	float lenght = this->Magnitude();
	if (lenght <= 0 ) 
		return;
	
	this->x /= lenght;
	this->y /= lenght;
}

Vector2D Vector2D::operator +(const Vector2D &v){
	Vector2D vector;
	vector.x = x + v.x;
	vector.y = y + v.y;

	return vector;
}

Vector2D Vector2D::operator +(const float &num){
	Vector2D vector;
	vector.x = x + num;
	vector.y = y + num;
	
	return vector;
}

Vector2D Vector2D::operator -(const Vector2D &v){
	Vector2D vector;
	vector.x = x - v.x;
	vector.y = y - v.y;

	return vector;
}

Vector2D Vector2D::operator -(const float &num){
	Vector2D vector;
	vector.x = x - num;
	vector.y = y - num;
	
	return vector;
}

Vector2D Vector2D::operator *(const float &num){
	Vector2D vector;
	vector.x = x * num;
	vector.y = y * num;

	return vector;
}

Vector2D Vector2D::operator /(const float &num){
	Vector2D vector;
	if(num != 0) 
	{
		vector.x = x / num;
		vector.y = y / num;
	}
	
	return vector;
}

bool Vector2D::operator ==(const Vector2D &v){
	if((x == v.x) && (y == v.y))
	{
		return true;
	} 
	else 
	{
		return false;
	}
}

void Vector2D::operator =(const Vector2D &v){
	this->x = v.x;
	this->y = v.y;
}

void Vector2D::operator +=(const Vector2D &v){
	this->x += v.x;
	this->y += v.y;
}

void Vector2D::operator +=(const float &num){
	this->x += num;
	this->y += num;
}

void Vector2D::operator -=(const Vector2D &v){
	this->x -= v.x;
	this->y -= v.y;
}

void Vector2D::operator -=(const float &num){
	this->x -= num;
	this->y -= num;
}

void Vector2D::operator *=(const float &num){
	this->x *= num;
	this->y *= num;
}

void Vector2D::operator /=(const float &num){
	if(num != 0)
	{
		this->x /= num;
		this->y /= num;
	}
}