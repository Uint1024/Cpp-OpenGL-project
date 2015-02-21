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
#include "Camera.h"


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

	const glm::vec2 getWindowSize() const {
		return window_size_;
	}

	SDL_Window* getWindow() {
		return window_;
	}

private:
	void							RenderWorld() const;
	SDL_Window* 					window_;
	GLfloat 						rectangle_vertices_[20];
	GLuint 							rectangle_ebo_elements_[6];
	GLuint 							rectangle_vao_;
	GLuint 							rectangle_vbo_;
	GLuint 							rectangle_ebo_;

	GLfloat							cube_vertices_[48];
	GLuint							cube_ebo_elements_[36];
	GLuint 							cube_vao_;
	GLuint 							cube_vbo_;
	GLuint 							cube_ebo_;


	std::unique_ptr<ShaderProgram> 	shader_program_;
	glm::mat4						view_;
	glm::mat4						projection_ortho_;
	glm::mat4						projection_perspective_;
	glm::vec2						window_size_;

	Camera							camera_;

};

extern float g_delta_time;
extern Engine g_engine;

#endif /* ENGINE_H_ */
