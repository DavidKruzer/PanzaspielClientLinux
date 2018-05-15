#include "stdafx.h"
#include "Background.h"

/* BACKGROUND.cpp*/

Background::Background()
{
}


Background::~Background()
{
}

void Background::init(GLuint texture, GLfloat* size, TextureManager* textureManager)
{
	this->size[0] = size[0];
	this->size[1] = size[1];
	location[0] = 0;
	location[1] = 0;
	rotation = 0;
	imageSprite.initImageSprite(texture, location, size, &rotation, textureManager);

}

void Background::draw(GLuint program)
{
	imageSprite.draw(program);
}