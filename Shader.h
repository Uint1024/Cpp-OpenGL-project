/*
 * Shader.h
 *
 *  Created on: 20 févr. 2015
 *      Author: John
 */

#ifndef SHADER_H_
#define SHADER_H_
#include <GL/glew.h>
#include <SDL_opengl.h>

class Shader {
public:
	Shader(const int shader_type, const GLchar* shader_file_name);
	virtual ~Shader();

	GLuint get_shader_id() const;
private:
	GLuint shader_id_;
};

#endif /* SHADER_H_ */
