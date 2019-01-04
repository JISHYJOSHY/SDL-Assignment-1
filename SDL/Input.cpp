#include "Input.h"

// public bools because this stuff is messy
Input::Input()
{
	right = left = down = up = esc = mouse = ctrl = shift = space = quit = false;
}

Input::~Input()
{
}

void Input::Update()
{
	// manage SDL input
	while (SDL_PollEvent(&incomingEvent))
	{
		switch (incomingEvent.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYUP:
			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				esc = false;
				break;
			case SDLK_SPACE:
				space = false;
				break;
			case SDLK_w:
			case SDLK_UP:
				up = false;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				down = false;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				left = false;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				right = false;
				break;
			case SDLK_LCTRL:
				ctrl = false;
				break;
			case SDLK_LSHIFT:
				shift = false;
				break;
			}
			break;

		case SDL_KEYDOWN:
			switch (incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				esc = true;
				break;
			case SDLK_SPACE:
				space = true;
				break;
			case SDLK_w:
			case SDLK_UP:
				up = true;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				down = true;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				left = true;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				right = true;
				break;
			case SDLK_LCTRL:
				ctrl = true;
				break;
			case SDLK_LSHIFT:
				shift = true;
				break;
			}
			break;

		case SDL_MOUSEMOTION:
			mousePos.x = incomingEvent.motion.x;
			mousePos.y = incomingEvent.motion.y;
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse = true;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse = false;
			break;
		}
	}
}