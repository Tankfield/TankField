#include "Menu.h"

Menu::Menu(SDL_Surface* screen, char* texture, TTF_Font* font, SDL_Color textColor)
: Object(new Texture(texture, screen), Vector2D(0,0)), font(font), textColor(textColor) {
	toRender = false;
	toCheckCollision = false;
	text = NULL;
	str = ""; 	
}

Menu::~Menu(){
	SDL_FreeSurface(text);
}

void Menu::typeCharacter(char c) {
	str += c;
	updateTypedTextTexture();
}

void Menu::deleteCharacter() {
	if (str.length() > 0) {
		str.erase(str.length() - 1);
	}

	updateTypedTextTexture();
}

void Menu::updateTypedTextTexture() {
	if (text != NULL) {
		SDL_FreeSurface(text);
		text = NULL;
	}

	text = TTF_RenderText_Solid(font, str.c_str(), textColor);
}

string Menu::getTypedText(){
	return str;
}

SDL_Surface* Menu::getTypedTextTexture() {
	return text;
}

void Menu::render(){
	this->texture->draw((int)this->position.x,(int)this->position.y);
}
