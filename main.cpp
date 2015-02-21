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
#include <math.h>//

#include "Game.h"
#include "InputManager.h"
#include "Engine.h"

int screen_width = 800;
int screen_height = 600;


Game g_game_data(screen_width, screen_height);
Engine g_engine(screen_width, screen_height);
float g_delta_time = 0.0f;

int main(int argc, char* args[])
{
	//fix for Eclipse's console!
	setvbuf (stdout, NULL, _IONBF, 0);

	bool running = true;
	Uint32 frame_time = 0;
	Uint32 diff = 0;
	Uint32 last_frame_time = 0;
	while (running)
	{
		frame_time = SDL_GetTicks();
		diff = frame_time - last_frame_time;
		g_delta_time = diff / 1000.0f;

		last_frame_time = frame_time;

		g_engine.Clear();
		running = InputManager::pollEvents();
		g_game_data.Update();
		g_engine.Update();
		g_engine.Swap();

	}
	/*glDeleteProgram(shader_program);
	glDeleteShader(fragment_shader);////
	glDeleteShader(vertex_shader);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);*/
	SDL_Quit();

	return 0;
}
