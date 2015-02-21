/*
 * Camera.cpp
 *
 *  Created on: 21 févr. 2015
 *      Author: John
 */

#include <iostream>
#include <SDL.h>
#include "Camera.h"
#include "InputManager.h"
#include "Engine.h"


Camera::Camera(	glm::vec3 	position,
				glm::vec3 	world_up,
				GLfloat 	yaw,
				GLfloat 	pitch,
				GLfloat 	movement_speed,
				GLfloat 	mouse_sensitivity) :
	position_(position),
	front_(glm::vec3(0.0f, 0.0f, -1.0f)),
	world_up_(world_up),
	yaw_(yaw),
	pitch_(pitch),
	mouse_sensitivity_(mouse_sensitivity),
	movement_speed_(movement_speed),
	zoom_(45.0f)
{
	updateCameraVectors();
}

Camera::~Camera()
{
	// TODO Auto-generated destructor stub
}

void
Camera::update()
{
	glm::vec2 mouse_movement = InputManager::getMouseMovement() * mouse_sensitivity_;
	yaw_   += mouse_movement.x;
	pitch_ -= mouse_movement.y;
	std::cout << "pitch=" << pitch_ << std::endl;
	std::cout << "yaw=" << yaw_ << std::endl;
	if(pitch_ > 89.0f)
	{
		pitch_ = 89.0f;
	}
	else if(pitch_ < -89.0f)
	{
		pitch_ = -89.0f;
	}

	GLfloat delta_speed = movement_speed_ * g_delta_time;
	auto keys_down = InputManager::getKeysDown();
	if(keys_down[SDL_SCANCODE_R])
	{
		position_ += front_ * delta_speed;
	}
	if(keys_down[SDL_SCANCODE_F])
	{
		position_ -= front_ * delta_speed;
	}
	if(keys_down[SDL_SCANCODE_D])
	{
		position_ -= right_ * delta_speed;
	}
	if(keys_down[SDL_SCANCODE_G])
	{
		position_ += right_ * delta_speed;
	}

	updateCameraVectors();
}

void
Camera::updateCameraVectors()
{
	front_.x 	= cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	front_.y 	= sin(glm::radians(pitch_));
	front_.z 	= sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
	right_ 		= glm::normalize(glm::cross(front_, world_up_));
	up_ 		= glm::normalize(glm::cross(right_, front_));
}

glm::mat4
Camera::getViewMatrix() const
{
	return glm::lookAt(position_, position_ + front_, world_up_);
}
