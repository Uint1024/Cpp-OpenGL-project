/*
 * InputManager.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */
#include <iostream>
#include <SDL.h>
#include "InputManager.h"


bool InputManager::pollEvents(){

	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			//running = false;
			return false;
		}

	}

	return true;
}
