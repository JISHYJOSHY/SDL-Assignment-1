#ifndef __sprite
#define __sprite

#include <string>
#include <SDL.h>
#include "Vec2.h"

// sprite class used to load in images
class Sprite
{
public:

	// constructors
	Sprite();
	Sprite(std::string filename, SDL_Renderer *renderer);
	~Sprite();

	// loading and getting the image
	bool LoadFromBMP(std::string filename, SDL_Renderer *renderer);
	SDL_Texture* GetTexture();

	// draw
	void Draw(int positionX, int positionY, SDL_Renderer *renderer);
	void Draw(Vec2 position, SDL_Renderer *renderer);

	// get width and height for collision purposes
	int GetW();
	int GetH();

protected:

	/// This variable will be our handle for the texture
	SDL_Texture *texture;
	int w, h;
};

#endif