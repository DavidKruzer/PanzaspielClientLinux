#pragma once
#include "Texture.h"

#define maxTextures 100

class TextureManager
{
private:
	GLuint textureCount = 0;

	GLuint boundTexture = maxTextures;

	Texture textures[maxTextures];
public:
	GLuint addTexture(const char*);
	void useTexture(GLuint);
	TextureManager();
	~TextureManager();
};