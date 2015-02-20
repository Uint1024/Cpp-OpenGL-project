/*
 * InputManager.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

class InputManager {
public:

	virtual ~InputManager();

	static bool pollEvents();

private:
	InputManager();
	static bool keys_down[1024];
};

#endif /* INPUTMANAGER_H_ */
