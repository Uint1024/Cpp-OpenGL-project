/*
 * Camera.h
 *
 *  Created on: 21 févr. 2015
 *      Author: John
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#define GLEW_STATIC

#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
class Camera {
public:
	Camera(	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			GLfloat yaw = -90.0f,
			GLfloat pitch = 0.0f,
			GLfloat movement_speed = 0.6f,
			GLfloat mouse_sensitivity = 0.2f);
	virtual ~Camera();
	void updateCameraVectors();
	void update();
	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 	position_;
	glm::vec3	front_;
	glm::vec3	up_;
	glm::vec3	right_;
	glm::vec3	world_up_;
	GLfloat		yaw_;
	GLfloat		pitch_;
	GLfloat		mouse_sensitivity_;
	GLfloat		movement_speed_;
	GLfloat		zoom_;

};

#endif /* CAMERA_H_ */
