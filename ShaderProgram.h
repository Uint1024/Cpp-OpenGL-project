/*
 * ShaderProgram.h
 *
 *  Created on: 20 févr. 2015
 *      Author: John
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL_opengl.h>

class Shader;
class ShaderProgram {
public:
	//TODO: variable number of shaders
	ShaderProgram(const Shader& shader1, const Shader& shader2);
	virtual ~ShaderProgram();
	void attachShader(GLuint shader_id);
	void bindFragDataLocation(GLint id, const GLchar* name);
	void use();
	GLuint getUniformLocation(const GLchar* name) const;
	GLuint getAttribLocation(const GLchar* name) const;
private:
	GLuint shader_program_id_;
};

#endif /* SHADERPROGRAM_H_ */
