
#include "Element.h"
#include "Image.h"

Image::Image() : Element() {

}

Image::Image(const char* imagePath) : Element(imagePath) {
}

Image::~Image() {
	//SDL_FreeSurface(texture);
}