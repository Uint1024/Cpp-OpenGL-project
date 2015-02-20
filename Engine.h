/*
 * Engine.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef ENGINE_H_
#define ENGINE_H_
#include <memory>
#include <GL/glew.h>
#include <glm.hpp>
#include <SDL.h>
#include "ShaderProgram.h"

namespace opengl
{
	void CheckProgramLinkStatus(GLuint program);
	void CheckShaderCompilationErrors(GLuint shader_id);
	void CheckOpenGLErrors();
	const char* ReadFileToString(const GLchar** file_name);
}

class Engine {
public:
				Engine	(const int screen_width, const int screen_height);
	virtual 	~Engine	();
	void 		Update	();
	void		DrawRectangle(const glm::vec3 position, const glm::vec3 size, const float angle = 0);
	void		Clear();
	void		Swap();
private:
	void							RenderWorld() const;
	SDL_Window* 					window_;
	GLfloat 						rectangle_vertices_[20];
	GLuint 							rectangle_vao_;
	GLuint 							rectangle_vbo_;
	GLuint 							rectangle_ebo_;
	GLuint 							rectangle_ebo_elements_[6];
	std::unique_ptr<ShaderProgram> 	shader_program_;
	glm::mat4						view_;
	glm::mat4						projection_;

};

extern Engine g_engine;

#endif /* ENGINE_H_ */
