#include "TextureFactory.h"
Texture2D* TextureFactory::Create(std::string filepath){

	Image* image = new Image;
	image->initWithImageFile(filepath);

	Texture2D* texture =new Texture2D;
	texture->initWithImage(image);

	return texture;

}