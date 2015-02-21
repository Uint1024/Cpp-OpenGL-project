/*
 * Engine.cpp

 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */
#define GLEW_STATIC
 #define GLM_FORCE_RADIANS
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>
#include "Engine.h"
#include "OpenGL.h"
#include "Math.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "InputManager.h"

//lalal

namespace opengl{
	void CheckProgramLinkStatus(GLuint program)
	{
		GLint program_success = GL_TRUE;
		glGetProgramiv(program, GL_LINK_STATUS, &program_success );
		if(program_success != GL_TRUE)
		{
			printf("Error linking program %d!\n", program);

			int info_length = 0;
			int max_length = 0;

			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
			char info_log[max_length];
			glGetProgramInfoLog(program, max_length, &info_length, info_log);
			if(info_length > 0){
				printf("%s\n", info_log);
			}

			//delete info_log;
		}
		else
		{
			printf("Linking successful.\n");
		}
	}

	void CheckShaderCompilationErrors(GLuint shader_id)
	{
		GLint success = GL_FALSE;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
		if(success == GL_FALSE)
		{
			perror("Error during shader compilation\n");
			int info_length = 0;
			int max_length = 0;

			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);
			char info_log[max_length];
			glGetShaderInfoLog(shader_id, max_length, &info_length, info_log);
			if(info_length > 0){
				printf("%s\n", info_log);
			}
		}
		else
		{
			printf("Compilation success, no error.\n");
		}
	}


	void CheckOpenGLErrors()
	{
		GLenum error = 0;
		error = glGetError();

		while((error = glGetError()) != GL_NO_ERROR)
		{
			switch(error)
			{
			case GL_INVALID_ENUM:
				printf("GL_INVALID_ENUM\n");
				break;
			case GL_INVALID_VALUE:
				printf("GL_INVALID_VALUE\n");
				break;
			case GL_INVALID_OPERATION:
				printf("GL_INVALID_OPERATION\n");
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				printf("GL_INVALID_FRAMEBUFFER_OPERATION\n");
				break;
			default:
				printf("Other error\n");
				break;
			}
		}
		printf("No more errors\n");
	}

	//open file_name, put its content in char_array and return it
	const char* ReadFileToString(const GLchar** file_name)
	{
		std::ifstream shader_file(*file_name);

		if(!shader_file){
			std::cout << "Can't open vertex_shader.gl" << std::endl;
		}
		std::string src_code((std::istreambuf_iterator<char>(shader_file)),
			std::istreambuf_iterator<char>());

		return src_code.c_str();


	}
}


Engine::Engine(const int screen_width, const int screen_height) :
rectangle_vertices_ {
		0,  0, 1.0, 0.0, 0.0, 	//top left
		1,  0, 0.0, 1.0, 0.0, 	//top right
		0, 1, 0.0, 0.0, 1.0, 	//bottom left
		1, 1, 0.0, 0.0, 0.0 	//bottom right
},
rectangle_ebo_elements_{
		0, 1, 2,
		2, 3, 1
},
/*cube_vertices_{
	0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//top left front 	0
	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//top left back 		1
	1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//top right front 	2
	1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//top right back 	3
	0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,//bottom left front 	4
	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//bottom left back 	5
	1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,//bottom right front 6
	1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f//bottom right back 	7
},*/
cube_vertices_{
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f,//top left front 	0
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,//top left back 		1
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,//top right front 	2
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f,//top right back 	3
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,//bottom left front 	4
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//bottom left back 	5
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f,//bottom right front 6
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f//bottom right back 	7
},
cube_ebo_elements_{
	4, 2, 0, //front a
	4, 2, 6, //front b
	5, 3, 1,//back a
	5, 3, 7, //back b
	4, 1, 0, //left a
	4, 1, 5, //left b
	6, 3, 2,//right a
	6, 3, 7,//right b
	0, 3, 1,//top a
	0, 3, 2,//top b
	4, 7, 5, //bottom a
	4, 7, 6//bottom b

},
window_size_(screen_width, screen_height),
camera_(glm::vec3(0.0f,0.0f,3.0f))
{
	SDL_Init(SDL_INIT_VIDEO);


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	window_ = SDL_CreateWindow("C++ OpenGL Pong",
							SDL_WINDOWPOS_UNDEFINED,
							SDL_WINDOWPOS_UNDEFINED,
							screen_width,
							screen_height,
							SDL_WINDOW_OPENGL );
	SDL_GLContext context = SDL_GL_CreateContext(window_);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if(glewError != GLEW_OK)
	{
		std::cout << "Error initializing GLEW!" << glewGetErrorString(glewError) << std::endl;
	}
	else
	{
		std::cout << "Glew OK" << std::endl;
	}

	glViewport( 0.f, 0.f, screen_width, screen_height );
	glEnable(GL_DEPTH_TEST);


/*
	//view_ = glm::translate(view_, glm::vec3(0.0f, 0.0f, 1.0f));
	//rectangle shape data			//vao id
	glGenVertexArrays(1, &rectangle_vao_);	//generate vao for this id
	glBindVertexArray(rectangle_vao_);		//bind the vao (make it active)

	//Creating vertex buffer object
	glGenBuffers(1, &rectangle_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, rectangle_vbo_);	//make buffer active
	glBufferData(GL_ARRAY_BUFFER, 		//transfer vertices data to the buffer
			sizeof(rectangle_vertices_),
			rectangle_vertices_,
			GL_STATIC_DRAW);

	//Create element array
	glGenBuffers(1, &rectangle_ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle_ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangle_ebo_elements_),
			rectangle_ebo_elements_, GL_STATIC_DRAW);*/


	/*LOADING SHADERS*/
	Shader vertex_shader(GL_VERTEX_SHADER, "vertex_shader.gl");
	Shader fragment_shader(GL_FRAGMENT_SHADER, "fragment_shader.gl");


	//Linking vertex and fragment shaders into a shader program
	shader_program_ = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
	shader_program_->bindFragDataLocation(0, "outColor");//


	//Specify the layout of the vertex data
	/*GLint pos_attribute = shader_program_->getAttribLocation("position");
	glEnableVertexAttribArray(pos_attribute);
	glVertexAttribPointer(pos_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint color_attribute = shader_program_->getAttribLocation("color");
	glEnableVertexAttribArray(color_attribute);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
			(void*)(2*sizeof(GLfloat)));*/


	//projection_ortho_ = glm::ortho(	0.0f, static_cast<float>(screen_width),static_cast<float>(screen_height), 0.0f,	-1.0f, 1.0f);
	projection_perspective_ = glm::perspective(glm::radians(70.0f), (float)screen_width/(float)screen_height, 0.1f, 100.0f);


	//GLuint projection_locaion = shader_program_->getUniformLocation("projection");
	//glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection_));

	glGenVertexArrays(1, &cube_vao_);
	glBindVertexArray(cube_vao_);
	glGenBuffers(1, &cube_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo_);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(cube_vertices_),
			cube_vertices_,
			GL_STATIC_DRAW);
	glGenBuffers(1, &cube_ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_ebo_elements_),
			cube_ebo_elements_, GL_STATIC_DRAW);

	//Specify the layout of the vertex data
	GLint pos_attribute = shader_program_->getAttribLocation("position");
	glEnableVertexAttribArray(pos_attribute);
	glVertexAttribPointer(pos_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	GLint color_attribute = shader_program_->getAttribLocation("color");
	glEnableVertexAttribArray(color_attribute);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(void*)(3*sizeof(GLfloat)));

	opengl::CheckOpenGLErrors();




	//unbinding everything
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Engine::~Engine() {
}

void Engine::Update() {
	camera_.update();
	SDL_ShowCursor(0);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	/*SDL_WarpMouseInWindow(	window_,
								window_size_.x/2.0f,
								window_size_.y/2.0f);*/
}

void Engine::Clear(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::Swap(){
	SDL_GL_SwapWindow(window_);
}
void Engine::DrawRectangle(const glm::vec3 position, const glm::vec3 size, const float angle) {
	GLfloat radius = 2.0f;
	GLfloat camX = sin(SDL_GetTicks()/1000.0f) * radius;
	GLfloat camZ = cos(SDL_GetTicks()/1000.0f) * radius;
	//std::cout << camX << std::endl;
	//view_ = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	view_ = camera_.getViewMatrix();
	shader_program_->use();
	glm::mat4 model;
	model = glm::translate(model, position);
	model = glm::scale(model, size);

	glm::mat4 total_projection = projection_perspective_;
	//math::PrintMatrice4Values(model);
	GLuint model_location = shader_program_->getUniformLocation("model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
	GLuint projection_location = shader_program_->getUniformLocation("projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(total_projection));
	GLuint view_location = shader_program_->getUniformLocation("view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view_));


	/*glBindVertexArray(rectangle_vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle_ebo_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/
	glBindVertexArray(cube_vao_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_ebo_);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Engine::RenderWorld() const {

}
