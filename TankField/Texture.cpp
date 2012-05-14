#include "Texture.h"

Texture::Texture(const char* filename, SDL_Surface *screen)
: displaySurface(screen) {
	this->surface = this->loadImage(filename);

	this->width = this->surface->w;
	this->height = this->surface->h;

};

Texture::Texture(const Texture &other){
	width = other.width;
	height = other.height;
	displaySurface = other.displaySurface;
	surface = SDL_DisplayFormatAlpha(other.surface);
}

Texture::~Texture(){
	SDL_FreeSurface(surface);
}

SDL_Surface* Texture::loadImage(const char *filename){
	return (SDL_DisplayFormatAlpha(IMG_Load(filename)));
}

void Texture::update(float timeSinceLastTime) 
{}


void Texture::draw(int x, int y){
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	SDL_BlitSurface(surface, NULL, displaySurface, &tempRect);
}

unsigned int Texture::getWidth(){
	return width;
}
unsigned int Texture::getHeight(){
	return height;
}

SDL_Rect Texture::getBounds()
{
	SDL_Rect bounds;

	bounds.x = 0;
	bounds.y = 0;
	bounds.w = width;
	bounds.h = height;

	return bounds;
}


void Texture::lock() {
	SDL_LockSurface(surface);
}

void Texture::unlock() {
	SDL_UnlockSurface(surface);
}

unsigned int Texture::getAlpha(int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    Uint32 pixelColor;
     
    switch(bpp) {
        case(1):
            pixelColor = *p;
            break;
        case(2):
            pixelColor = *(Uint16*)p;
            break;

        case(3):
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                pixelColor = p[0] << 16 | p[1] << 8 | p[2];
            else
                pixelColor = p[0] | p[1] << 8 | p[2] << 16;
            break;
        case(4):
            pixelColor = *(Uint32*)p;
            break;
    }
     
    Uint8 red, green, blue, alpha;
    SDL_GetRGBA(pixelColor, surface->format, &red, &green, &blue, &alpha);
 
    return alpha;
}