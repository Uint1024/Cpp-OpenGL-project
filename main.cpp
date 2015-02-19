/*
 * main.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */



#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <ios>
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <stdbool.h>
#include <math.h>

int screen_width = 800;
int screen_height = 600;

namespace Math
{
	void PrintMatrice4Values(glm::mat4 mat4)
	{
		std::cout << std::endl;
		for(int y = 0 ; y < 4 ; ++y)

		{
			for(int x = 0 ; x < 4 ; ++x)
			{
				std::cout << mat4[x][y] << ";";
			}
			std::cout << std::endl;
		}
	}
}


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
			perror("Error during vertex shader compilation\n");
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

	//oen file_name, put its content in char_array, return the char array's size
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


int main(int argc, char* args[])
{

	//fix for Eclipse's console!
	setvbuf (stdout, NULL, _IONBF, 0);

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_Window* window = SDL_CreateWindow(	"C OpenGL",
											SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
											screen_width,
											screen_height,
											SDL_WINDOW_OPENGL );

	SDL_GLContext context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if( glewError != GLEW_OK )
	{
		printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
	}
	else
	{
		printf("Glew OK");
	}


	bool running = true;

	SDL_Event e;




	//Creating vertex array object
	GLuint vao; 				//vao id
	glGenVertexArrays(1, &vao);	//generate vao for this id
	glBindVertexArray(vao);		//bind the vao (make it active)

	//Creating vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	GLfloat vertices[] = {
			-0.5,  0.5, 1.0, 0.0, 0.0, 	//top left
			 0.5,  0.5, 0.0, 1.0, 0.0, 	//top right
			 0.5, -0.5, 0.0, 0.0, 1.0, 	//bottom left
			-0.5, -0.5, 0.0, 0.0, 0.0 	//bottom right
	};



	glBindBuffer(GL_ARRAY_BUFFER, vbo);	//make buffer active
	glBufferData(GL_ARRAY_BUFFER, 		//transfer vertices data to the buffer
			sizeof(vertices),
			vertices,
			GL_STATIC_DRAW);

	//Create element array
	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
			0, 1, 2,
			2, 3, 0
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	//Reading and compiling the shader sources
	//vertex

	const GLchar* vertex_shader_file_name = "vertex_shader.gl";
	const char* vertex_shader_source = opengl::ReadFileToString(
															&vertex_shader_file_name);
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const GLchar* const*)&vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	opengl::CheckShaderCompilationErrors(vertex_shader);


	//fragment
	const char* fragment_shader_file_name = "fragment_shader.gl";
	const GLchar* fragment_shader_source = opengl::ReadFileToString(
			&fragment_shader_file_name);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const GLchar* const*)&fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	opengl::CheckShaderCompilationErrors(fragment_shader);

	//Linking vertex and fragment shaders into a shader program
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glBindFragDataLocation(shader_program, 0, "outColor");
	glLinkProgram(shader_program);

	opengl::CheckProgramLinkStatus(shader_program);

	glUseProgram(shader_program);

	//Specify the layout of the vertex data
	GLint pos_attribute = glGetAttribLocation(shader_program, "position");
	glEnableVertexAttribArray(pos_attribute);
	glVertexAttribPointer(pos_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint color_attribute = glGetAttribLocation(shader_program, "color");
	glEnableVertexAttribArray(color_attribute);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
			(void*)(2*sizeof(GLfloat)));




	glm::vec3 position(0.0f, 0.0f, 0.0f);
	while (running)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);


		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

			if (state[SDL_SCANCODE_W])
			{
				position.y += 0.01f;

			}
			if (state[SDL_SCANCODE_S])
			{
				position.y -= 0.01f;

			}

		}

		glm::mat4 view;
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		position.x = cos(SDL_GetTicks()/1000.0f);
		position.y = sin(SDL_GetTicks()/1000.0f);
		//position.x = cos

		glm::mat4 projection = glm::perspective(45.0f,
				(float)screen_width/(float)screen_height,
				0.1f, 100.0f);

		glm::mat4 model;
		float angle =  SDL_GetTicks() / 10 %360;
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));

		/*GLuint transform_location = glGetUniformLocation(shader_program, "transform");
		glUniformMatrix4fv(transform_location, 1, GL_FALSE, glm::value_ptr(trans));
*/
		GLuint model_location = glGetUniformLocation(shader_program, "model");
		GLuint view_location = glGetUniformLocation(shader_program, "view");
		GLuint projection_location = glGetUniformLocation(shader_program, "projection");
		glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));


		vertices[2] = 1;
		vertices[3] = 1;
		vertices[4] = 1;

		vertices[7] = cos((SDL_GetTicks() + 2000)/1000.0f);
		vertices[8] = sin((SDL_GetTicks() + 8500)/1000.0f);
		vertices[9] = cos((SDL_GetTicks() + 1294)/1000.0f);

		vertices[12] = cos((SDL_GetTicks() + 8960)/1000.0f);
		vertices[13] = sin((SDL_GetTicks() + 1230)/1000.0f);
		vertices[14] = cos((SDL_GetTicks() + 7803)/1000.0f);


		vertices[17] = cos((SDL_GetTicks() + 1236)/1000.0f);
		vertices[18] = sin((SDL_GetTicks() + 10001)/1000.0f);
		vertices[19] = cos((SDL_GetTicks() + 8960)/1000.0f);

		glBufferData(GL_ARRAY_BUFFER, 		//transfer vertices data to the buffer
					sizeof(vertices),
					vertices,
					GL_STATIC_DRAW);

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);

	}
	glDeleteProgram(shader_program);
	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	SDL_DestroyWindow(window);

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}
