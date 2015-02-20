/*
 * Game.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef GAME_H_
#define GAME_H_

class GameObject;
class Game {
public:
	Game(const int screen_width, const int screen_height);
	virtual ~Game();
	void Update();

private:

	GameObject* racket[2];
};

extern Game g_game_data;
#endif /* GAME_H_ */
