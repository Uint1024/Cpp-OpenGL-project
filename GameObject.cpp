/*
 * GameObject.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */


#include <iostream>
#include "GameObject.h"
#include "Engine.h"

GameObject::GameObject(const glm::vec3 position, const glm::vec3 size, const float angle) :
position_(position),
size_(size),
angle_(angle)

{
	// TODO Auto-generated constructor stub

}

GameObject::~GameObject() {
	// TODO Auto-generated destructor stub
}

void GameObject::Update() {
	g_engine.DrawRectangle(position_, size_, 0.0f);
}
