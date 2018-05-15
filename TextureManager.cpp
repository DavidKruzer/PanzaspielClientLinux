#include "stdafx.h"
#include "TextureManager.h"

/*
* TextureManager.cpp
*
*  Created on: 28.12.2017
*      Author: david
*/

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::useTexture(GLuint textureIndex) {
	if (textureIndex != boundTexture) {
		textures[textureIndex].bindTexture();
		boundTexture = textureIndex;
	}
}

GLuint TextureManager::addTexture(const char* texturePath) {
	if (textureCount < maxTextures) {
		textures[textureCount].generateTexture(texturePath);
		return (textureCount++); //aktuelle nummer zurückgeben, dann 1 addieren
	}
	return 0;
}