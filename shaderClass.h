#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename); // The function is irrelevant to OpenGL, it just output the content as string

class Shader // Basically an OpenGL program that is nicely wrapped up
{
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentfile);

		void Activate();
		void Delete();
};

#endif // !SHADER_CLASS_H

