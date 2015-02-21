/*
 * Ball.h
 *
 *  Created on: 20 févr. 2015
 *      Author: John
 */

#ifndef BALL_H_
#define BALL_H_

#include "GameObject.h"

class Ball: public GameObject {
public:
	Ball(const glm::vec3 position, const glm::vec3 size, const float angle,
			const float speed);
	virtual ~Ball();
	void update() override;


};

#endif /* BALL_H_ */
