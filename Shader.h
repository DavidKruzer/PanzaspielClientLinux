#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

#define SHADER_H

class Shader
{
private:
public:
	GLuint Program;

	Shader(const GLchar*, const GLchar*);
	void Use();
	~Shader();
};