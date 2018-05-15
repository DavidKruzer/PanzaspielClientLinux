#include "stdafx.h"
#include "Scene.h"


/*
* Scene.cpp
*
*  Created on: 28.12.2017
*      Author: david
*/

//Scene manages all ImageSprites, Animations and the Camera

void Scene::init()
{
	textureManager = new TextureManager();
	myShader = new Shader("Shader\\Vertex_Shader", "Shader\\Fragment_Shader");
	myShader->Use();

	this->program = myShader->Program;
}

void Scene::setBackground(GLfloat* size, GLuint backgroundTexture)
{
	background.init(backgroundTexture, size, textureManager);
}

void Scene::setViewModel(ViewModel viewModel)
{
	this->viewModel = viewModel;
}

ImageSprite* Scene::addImageSprite(GLuint texture, GLfloat* location, GLfloat* size, GLfloat* rotation)
{
	if (imageSpriteCount < maxImageSprites)
	{
		imageSprites[imageSpriteCount].initImageSprite(texture, location, size, rotation, textureManager);
		imageSpriteCount++;
		return &imageSprites[imageSpriteCount - 1];
	}
	return NULL;
}

Animation* Scene::addAnimation(GLuint* textures, GLuint textureAmount, GLfloat* location, GLfloat* size, GLfloat rotation, GLboolean loop)
{
	if (animationCount < maxAnimations)
	{
		animations[animationCount].newAnimation(location, size, rotation, 0.07f, textures, textureAmount, loop, textureManager);
		animationCount++;
		return &animations[animationCount - 1];
	}
	return NULL;
}

void Scene::draw(GLfloat passedTime)
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	background.draw(program);
	for (GLuint i = 0; i < imageSpriteCount; i++)
	{
		textureManager->useTexture(imageSprites[i].texture);
		imageSprites[i].draw(program);
	}

	for (GLuint i = 0; i < animationCount; i++)
	{
		if (animations[i].draw(passedTime, program)) //Animation finished
		{
			//replace finished animation with last animation
			animationCount--;
			memcpy(&animations[i], &animations[animationCount], sizeof(Animation));
		}
	}
}


Scene::Scene()
{
}


Scene::~Scene()
{
}
