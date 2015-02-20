/*
 * Game.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */


#include "Engine.h"
#include "Game.h"
#include "GameObject.h"


Game::Game(const int screen_width, const int screen_height) {
	racket[0] = new GameObject(glm::vec3(200.0f, 200.0f, 0.0f),
								glm::vec3(10.0f, 200.0f, 0.0f),
								0.0f);

}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::Update() {
	racket[0]->Update();
}
