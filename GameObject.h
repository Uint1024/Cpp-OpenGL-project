/*
 * GameObject.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include <glm.hpp>

class GameObject {
public:
	GameObject(const glm::vec3 position, const glm::vec3 size, const float angle);
	virtual ~GameObject();
	void Update();

private:
	glm::vec3 position_;
	glm::vec3 size_;
	float angle_;
};

#endif /* GAMEOBJECT_H_ */
