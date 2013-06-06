#ifndef _Menu_H
#define _Menu_H

#include <SDL/SDL.h>
#include "Object.h"
#include <SDL/SDL_ttf.h>
#include <string>

using namespace std;

class Menu : public Object{
private:
	string str; 
	SDL_Surface *text;
	TTF_Font *font;
	SDL_Color textColor;

public:	
	Menu(SDL_Surface* screen, char* texture, TTF_Font* font, SDL_Color textColor);
	~Menu();

	string getTypedText();

	virtual void render();

	void typeCharacter(char c);
	void deleteCharacter();

	SDL_Surface* getTypedTextTexture();
	void updateTypedTextTexture();
};



#endif