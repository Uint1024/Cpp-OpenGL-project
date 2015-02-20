/*
 * Shader.cpp
 *
 *  Created on: 20 févr. 2015
 *      Author: John
 */
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL_opengl.h>
#include "Shader.h"
#include "Engine.h"


Shader::Shader(const int shader_type, const GLchar* shader_file_name)
{
	shader_id_ = glCreateShader(shader_type);
	const char* vertex_shader_source = opengl::ReadFileToString(&shader_file_name);
	glShaderSource(shader_id_, 1, (const GLchar* const*)&vertex_shader_source, NULL);
	glCompileShader(shader_id_);
	opengl::CheckShaderCompilationErrors(shader_id_);
}

Shader::~Shader()
{
	// TODO Auto-generated destructor stub
}

GLuint Shader::get_shader_id() const
{
	return shader_id_;
}

