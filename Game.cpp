/*
 * Game.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */


#include "Engine.h"
#include "Game.h"
#include "GameObject.h"


Game::Game(const int screen_width, const int screen_height) :
ball(glm::vec3(screen_width/2.0f, screen_height/2.0f, 0.0f),
		glm::vec3(20.0f, 20.0f, 0.0f),
		135.0f, 300.0f)
{
	racket[0] = new GameObject(glm::vec3(50.0f, 200.0f, 0.0f),
								glm::vec3(50.0f, 200.0f, 0.0f),
								0.0f, 360.0f, true);
	racket[1] = new GameObject(glm::vec3(screen_width - 50.0f - 50.0f, 200.0f, 0.0f),
									glm::vec3(50.0f, 200.0f, 0.0f),
									0.0f, 250.0f, false);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::Update() {
	racket[0]->update();
	//racket[1]->update();
	//ball.update();
}
