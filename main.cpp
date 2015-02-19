/*
 * main.cpp
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */



#define GLEW_STATIC
#include <iostream>

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


/*
void OpenGL_CheckProgramLinkStatus(GLuint program)
{
	GLint program_success = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &program_success );
	if(program_success != GL_TRUE)
	{
		printf("Error linking program %d!\n", program);

		int info_length = 0;
		int max_length = 0;

		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
		char* info_log = calloc(1, max_length+1);
		glGetProgramInfoLog(program, max_length, &info_length, info_log);
		if(info_length > 0){
			printf("%s\n", info_log);
		}

		free(info_log);
	}
	else
	{
		printf("Linking successful.\n");
	}
}

void OpenGL_CheckShaderCompilationErrors(GLuint shader_id)
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


void OpenGL_CheckOpenGLErrors()
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

//open file_name, put its content in char_array, return the char array's size
int OpenGL_ReadFileToString(GLchar** char_array, char** file_name)
{
	FILE *fp = NULL;
	int fSize = 0;
	fp = fopen(*file_name, "rb");

	if(!fp)
	{
		perror("Can't open vertex_shader.gl");
	}

	fseek(fp, 0, SEEK_END);
	fSize = ftell(fp);
	rewind(fp);

	*char_array = calloc(1, fSize+1);

	if(!char_array)
	{
		fclose(fp);
		fputs("Memory alloc fails", stderr);
	}


	if(fread(*char_array, fSize, 1, fp) != 1)
	{

		fclose(fp);
		free(*char_array);
		fputs("Read file fails", stderr);
	}
	fclose(fp);



	return fSize;
}
*/

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




	/*//Creating vertex array object
	GLuint vao; 				//vao id
	glGenVertexArrays(1, &vao);	//generate vao for this id
	glBindVertexArray(vao);		//bind the vao (make it active)

	//Creating vertex buffer object
	GLuint vbo;
	glGenBuffers(1, &vbo);
	GLfloat vertices[] = {
			-0.5,  0.5, 0.0, 0.0, 0.0, 	//top left
			 0.5,  0.5, 0.0, 0.0, 0.0, 	//top right
			 0.5, -0.5, 0.0, 0.0, 0.0, 	//bottom left
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

	GLchar* vertex_shader_source = NULL;
	char* vertex_shader_file_name = "vertex_shader.gl";
	int size = OpenGL_ReadFileToString(&vertex_shader_source, &vertex_shader_file_name);
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const GLchar* const*)&vertex_shader_source, &size);
	glCompileShader(vertex_shader);
	OpenGL_CheckShaderCompilationErrors(vertex_shader);


	//fragment
	GLchar* fragment_shader_source = NULL;
	char* fragment_shader_file_name = "fragment_shader.gl";
	OpenGL_ReadFileToString(&fragment_shader_source, &fragment_shader_file_name);
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, (const GLchar* const*)&fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	OpenGL_CheckShaderCompilationErrors(fragment_shader);

	//Linking vertex and fragment shaders into a shader program
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glBindFragDataLocation(shader_program, 0, "outColor");
	glLinkProgram(shader_program);

	OpenGL_CheckProgramLinkStatus(shader_program);

	glUseProgram(shader_program);

	//Specify the layout of the vertex data
	GLint pos_attribute = glGetAttribLocation(shader_program, "position");
	glEnableVertexAttribArray(pos_attribute);
	glVertexAttribPointer(pos_attribute, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint color_attribute = glGetAttribLocation(shader_program, "color");
	glEnableVertexAttribArray(color_attribute);
	glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat),
			(void*)(2*sizeof(GLfloat)));



*/
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	//Math::PrintMatrice4Values(trans);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	Math::PrintMatrice4Values(trans);
	vec = trans * vec;

	std::cout << vec.x << vec.y << vec.z << std::endl;

	while (running)
	{
		/*vertices[2] = sin(SDL_GetTicks()/1000.0f);
		vertices[3] = cos(SDL_GetTicks()/1000.0f);
		vertices[4] = cos((SDL_GetTicks() + 1000)/1000.0f);

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
					GL_STATIC_DRAW);*/
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);

	}
	/*glDeleteProgram(shader_program);
	glDeleteShader(fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);*/
	SDL_DestroyWindow(window);

	SDL_GL_DeleteContext(context);
	SDL_Quit();

	return 0;
}
