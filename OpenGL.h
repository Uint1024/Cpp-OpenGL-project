/*
 * OpenGL.h
 *
 *  Created on: 19 févr. 2015
 *      Author: John
 */

#ifndef OPENGL_H_
#define OPENGL_H_

namespace opengl{
	void CheckProgramLinkStatus(GLuint program);
	void CheckShaderCompilationErrors(GLuint shader_id);
	void CheckOpenGLErrors();
	const char* ReadFileToString(const GLchar** file_name);
}
#endif /* OPENGL_H_ */
