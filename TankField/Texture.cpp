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

SDL_Rect Texture::getBounds(){
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

void Texture::reloadTexture(const char* filename){
	this->surface = this->loadImage(filename);
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

void Texture::drawCircle(unsigned int cx, unsigned int cy, unsigned int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) { 
	Uint32 pixel = SDL_MapRGBA(surface->format, r, g, b, a);	

    for (double dy = 1; dy <= radius; dy += 1.0) { 
        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;
 
		if ((cy+radius-dy < surface->h) && (x < surface->w)) {
			Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + radius - dy)) * surface->pitch + x * surface->format->BytesPerPixel;
			Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - radius + dy)) * surface->pitch + x * surface->format->BytesPerPixel;;
 
			for (; x <= cx + dx; x++){
				*(Uint32 *)target_pixel_a = pixel;
				target_pixel_a += surface->format->BytesPerPixel;

				*(Uint32 *)target_pixel_b = pixel;				
				target_pixel_b += surface->format->BytesPerPixel;
			}
		}
    }
}