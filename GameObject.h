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
	GameObject(const glm::vec3 position, const glm::vec3 size, const float angle,
			const float speed, const bool is_player);
	virtual ~GameObject();
	virtual void update();
	virtual void render();

	float getAngle() const {
		return angle_;
	}

	void setAngle(float angle) {
		angle_ = angle;
	}

	const glm::vec3& getPosition() const {
		return position_;
	}

	void setPosition(const glm::vec3& position) {
		position_ = position;
	}

	const glm::vec3& getSize() const {
		return size_;
	}

	void setSize(const glm::vec3& size) {
		size_ = size;
	}

	float getSpeed() const {
		return speed_;
	}

	void setSpeed(float speed) {
		speed_ = speed;
	}

protected:
	glm::vec3 	position_;
	glm::vec3 	size_;
	float 		angle_;
	float 		speed_;
	bool		player_;
	//Bbox		bbox_;
};

#endif /* GAMEOBJECT_H_ */
