#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Other Libs
#include <SOIL.h>


class Texture
{
private:
	GLuint texture;
public:
	Texture();
	void generateTexture(const char*);
	void bindTexture();
	~Texture();
};