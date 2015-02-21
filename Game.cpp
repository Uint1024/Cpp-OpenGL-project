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
ball(glm::vec3(2.0f, 1.0f, 0.0f),
		glm::vec3(0.3f, 0.3f, 0.0f),
		135.0f, 2.0f)
{
	racket[0] = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f),
								glm::vec3(0.36f, 1.0f, 0.36f),
								0.0f, 0.6f, true);
	racket[1] = new GameObject(glm::vec3(5.0f - 0.36f, 0.0f, 0.0f),
			glm::vec3(0.36f, 1.0f, 0.36f),
											0.0f, 0.6f, true);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::Update() {
	racket[0]->update();
	racket[1]->update();
	ball.update();
}
