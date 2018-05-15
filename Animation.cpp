#include "stdafx.h"
#include "Animation.h"

/*
* Animation.cpp
*
*  Created on: 07.01.2018
*      Author: david
*/

Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::newAnimation(GLfloat* location, GLfloat* size, GLfloat rotation, GLfloat timePerTexture, GLuint* textures, GLuint textureAmount, GLboolean loop, TextureManager* textureManager)
{
	this->location[0] = location[0];
	this->location[1] = location[1];
	this->size[0] = size[0];
	this->size[1] = size[1];
	this->timePerTexture = timePerTexture;
	this->textures = new GLuint[textureAmount];
	memcpy(this->textures, textures, sizeof(GLuint) * textureAmount);
	this->textureAmount = textureAmount;
	this->rotation = rotation;
	this->imageSprite.initImageSprite(textures[0], this->location, this->size, &this->rotation, textureManager);
	this->loop = loop;
	timeFromStart = 0;
}

//return weather animation finished
GLboolean Animation::draw(GLfloat passedTime, GLuint program)
{
	timeFromStart += passedTime;

	//textureNumber of Texture that should currently show
	GLuint textureNumber = (GLuint)(timeFromStart / timePerTexture);

	if (textureNumber >= textureAmount)
	{
		//Animation went through entire iteration, restart when Animation is looped, else stop it
		if (loop)
		{
			textureNumber = textureNumber % textureAmount;
		}
		else
		{
			//delete Array holding Textures
			delete textures;
			return true;
		}
	}
	imageSprite.texture = textures[textureNumber];
	imageSprite.draw(program);
	return false;
}