/*
 * Game.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef GAME_H_
#define GAME_H_
#include "Ball.h"

class GameObject;
class Game {
public:
	Game(const int screen_width, const int screen_height);
	virtual ~Game();
	void Update();

	const Ball& getBall() const {
		return ball;
	}

	void setBall(const Ball& ball) {
		this->ball = ball;
	}

	GameObject** getRacket() {
		return racket;
	}

private:

	GameObject* racket[2];
	Ball		ball;
};

extern Game g_game_data;
#endif /* GAME_H_ */
