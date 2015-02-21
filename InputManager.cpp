/*
 * InputManager.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */
#include <iostream>
#include <SDL.h>
#include "InputManager.h"
#include <glm.hpp>
#include "Engine.h"

bool InputManager::keys_down[1024]{false};

glm::vec2 InputManager::previous_mouse_position_;
glm::vec2 InputManager::current_mouse_position_;
glm::vec2 InputManager::mouse_movement_;

bool InputManager::pollEvents(){

	SDL_Event e;

	mouse_movement_.x = 0.0f;
	mouse_movement_.y = 0.0f;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
				e.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
		{
			//running = false;
			return false;
		}

		if(e.type == SDL_KEYDOWN)
		{
			keys_down[e.key.keysym.scancode] = true;
		}

		if(e.type == SDL_KEYUP)
		{
			keys_down[e.key.keysym.scancode] = false;
		}

		if(e.type == SDL_MOUSEMOTION)
		{
			mouse_movement_.x = e.motion.xrel;
			mouse_movement_.y = e.motion.yrel;
		}

	}



	//SDL_SetRelativeMouseMode(SDL_TRUE);

	/*int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	current_mouse_position_.x = mouse_x;
	current_mouse_position_.y = mouse_y;*/


	//mouse_movement_ = previous_mouse_position_ - current_mouse_position_;
	//previous_mouse_position_ = current_mouse_position_;




	return true;
}
