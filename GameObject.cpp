/*
 * GameObject.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */


#include <iostream>
#include <SDL.h>
#include "GameObject.h"
#include "Engine.h"
#include "InputManager.h"
#include "Game.h"


GameObject::GameObject(const glm::vec3 position,
		const glm::vec3 size,
		const float angle,
		const float speed,
		const bool is_player) :
position_(position),
size_(size),
angle_(angle),
speed_(speed),
player_(is_player)
{
	// TODO Auto-generated constructor stub

}

GameObject::~GameObject()
{
	// TODO Auto-generated destructor stub
}

void
GameObject::render()
{
	g_engine.DrawRectangle(position_, size_, 0.0f);
}

void
GameObject::update()
{

	render();

	glm::vec2 movement(0.0f, 0.0f);
	if(player_)
	{
		if(InputManager::getKeysDown()[SDL_SCANCODE_W])
		{
			movement.y = -speed_ * g_delta_time;
		}
		if(InputManager::getKeysDown()[SDL_SCANCODE_S])
		{
			movement.y = speed_ * g_delta_time;
		}
	}
	else
	{
		if(g_game_data.getBall().getPosition().y > position_.y + size_.y/2.0f)
		{
			movement.y = speed_ * g_delta_time;
		}
		else
		{
			movement.y = -speed_ * g_delta_time;
		}
	}

	if(movement.y + position_.y < 0)
	{
		movement.y = 0;
	}
	if(movement.y + size_.y + position_.y >= g_engine.getWindowSize().y)
	{
		movement.y = 0;
	}

	position_.y += movement.y;

}
