#include <iostream>

#include "Sprite.h"

// set teture to NULL before loading image
Sprite::Sprite()
{
	texture = NULL;
}

Sprite::Sprite(std::string filename, SDL_Renderer *renderer)
{
	texture = NULL;
	this->LoadFromBMP(filename, renderer);
}

Sprite::~Sprite()
{
	// destroy image
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}

bool Sprite::LoadFromBMP(std::string filename, SDL_Renderer *renderer)
{
	// load an image from filename
	if (filename.empty())
	{
		std::cerr << "No filename given" << std::endl;
		return false;
	}

	// create a surface from image
	SDL_Surface * image = SDL_LoadBMP(filename.c_str());
	
	// color key magenta (255, 0, 255) out of image to add 'transparency'
	SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 0, 255));

	w = image->w;
	h = image->h;

	if (!image)
	{
		std::cerr << "Cannot find " << filename << ", please relocate file" << std::endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	return true;
}

SDL_Texture* Sprite::GetTexture()
{
	return texture;
}

void Sprite::Draw(int positionX, int positionY, SDL_Renderer *renderer)
{
	SDL_Rect destRect;

	destRect.x = positionX;
	destRect.y = positionY;

	SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void Sprite::Draw(Vec2 position, SDL_Renderer *renderer)
{
	SDL_Rect destRect;

	destRect.x = position.x;
	destRect.y = position.y;

	SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

int Sprite::GetW()
{
	return w;
}

int Sprite::GetH()
{
	return h;
}