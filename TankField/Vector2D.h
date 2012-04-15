#ifndef _Vector2D_H
#define _Vector2D_H

#define DEG2RAD 3.1415926535897932f / 180.0f 


class Vector2D{
	public: 
		Vector2D();
		Vector2D(float x, float y);  
		Vector2D(float angle); 
		 
		float x,y; 
		
		float Magnitude (); 
		void Normalize(); 							
		Vector2D operator +(const Vector2D &v); 
		Vector2D operator +(const float &num); 
		Vector2D operator -(const Vector2D &v);
		Vector2D operator -(const float &num); 
		Vector2D operator *(const float &num); 
		Vector2D operator /(const float &num);	
		bool operator ==(const Vector2D &v); 
		void operator =(const Vector2D &v); 
		void operator +=(const Vector2D &v); 
		void operator +=(const float &num); 
		void operator -=(const Vector2D &v);
		void operator -=(const float &num); 
		void operator *=(const float &num); 
		void operator /=(const float &num); 


};



#endif