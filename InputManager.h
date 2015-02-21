/*
 * InputManager.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <glm.hpp>


class InputManager {
public:

	virtual ~InputManager();

	static bool pollEvents();
	static bool* getKeysDown()
	{
		return keys_down;
	}

	static glm::vec2& getCurrentMousePosition() {
		return current_mouse_position_;
	}

	static glm::vec2& getMouseMovement()  {
		return mouse_movement_;
	}

	static glm::vec2& getPreviousMousePosition() {
		return previous_mouse_position_;
	}

private:
	InputManager();
	static bool 		keys_down[1024];
	static glm::vec2 	previous_mouse_position_;
	static glm::vec2 	current_mouse_position_;
	static glm::vec2 	mouse_movement_;
};


#endif /* INPUTMANAGER_H_ */
