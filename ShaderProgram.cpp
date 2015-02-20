/*
 * ShaderProgram.cpp
 *
 *  Created on: 20 févr. 2015
 *      Author: John
 */

#include "ShaderProgram.h"
#include "Engine.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const Shader& shader1, const Shader& shader2)
{
	shader_program_id_ =  glCreateProgram();
	glAttachShader(shader_program_id_, shader1.get_shader_id());
	glAttachShader(shader_program_id_, shader2.get_shader_id());
	glLinkProgram(shader_program_id_);
	opengl::CheckProgramLinkStatus(shader_program_id_);

}

ShaderProgram::~ShaderProgram()
{
	// TODO Auto-generated destructor stub
}

void
ShaderProgram::attachShader(GLuint shader_id)
{
}

void
ShaderProgram::bindFragDataLocation(GLint id, const GLchar* name)
{
	glBindFragDataLocation(shader_program_id_, id, name);
}

void
ShaderProgram::use()
{
	glUseProgram(shader_program_id_);
}

GLuint
ShaderProgram::getUniformLocation(const GLchar* name) const
{
	return glGetUniformLocation(shader_program_id_, name);
}

GLuint
ShaderProgram::getAttribLocation(const GLchar* name) const
{
	return glGetAttribLocation(shader_program_id_, name);
}


