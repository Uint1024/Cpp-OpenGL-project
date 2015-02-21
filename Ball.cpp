/*
 * Ball.cpp
 *
 *  Created on: 20 févr. 2015
 *      Author: John
 */


#include <iostream>
#include <glm.hpp>
#include "Ball.h"
#include "Game.h"
#include "Engine.h"


Ball::Ball(const glm::vec3 position, const glm::vec3 size, const float angle,
		const float speed) :
GameObject(position, size, angle, speed, false)
{
	// TODO Auto-generated constructor stub

}

Ball::~Ball()
{
	// TODO Auto-generated destructor stub
}

void
Ball::update()
{

	render();
	position_.y += sin(glm::radians(angle_)) * speed_ * g_delta_time;
	position_.x += cos(glm::radians(angle_)) * speed_ * g_delta_time;

	GameObject* racket_1 = g_game_data.getRacket()[0];
	GameObject* racket_2 = g_game_data.getRacket()[1];

	if(position_.x <= racket_1->getPosition().x + racket_1->getSize().x &&
			position_.y + size_.y > racket_1->getPosition().y &&
			position_.y < racket_1->getPosition().y + racket_1->getSize().y)
	{
		angle_ = 180.0f - angle_;
	}
	if(position_.x + size_.x >= racket_2->getPosition().x &&
				position_.y + size_.y > racket_2->getPosition().y &&
				position_.y < racket_2->getPosition().y + racket_2->getSize().y)
	{
		angle_ = 180.0f + angle_;
	}

	if(position_.y + size_.y > 2.5f ||
			position_.y < 0.0f)
	{
		angle_ = - angle_;
	}

}
