#ifndef __input
#define __input

#include <SDL.h>
#include "Vec2.h"

// input class to clean up game loop

class Input
{
public:
	Input();
	~Input();
	void Update();

	bool up, down, left, right, esc, mouse, ctrl, shift, space, quit;
	Vec2 mousePos;

private:
	SDL_Event incomingEvent;
};

#endif