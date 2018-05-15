#pragma once
#include "ImageSprite.h"
#include "Background.h"
#include "Animation.h"
#include "ViewModel.h"
#include "Shader.h"

#define maxImageSprites 200

#define maxAnimations 100

class Scene
{
private:

	ImageSprite imageSprites[maxImageSprites];
	Animation animations[maxAnimations];
	Background background;

	GLuint imageSpriteCount = 0;
	GLuint animationCount = 0;

	ViewModel viewModel;

public:
	TextureManager * textureManager;
	GLuint program;
	Shader* myShader;

	void init();
	void setBackground(GLfloat*, GLuint);
	void setViewModel(ViewModel);
	ImageSprite* addImageSprite(GLuint, GLfloat*, GLfloat*, GLfloat*);
	Animation* addAnimation(GLuint*, GLuint, GLfloat*, GLfloat*, GLfloat, GLboolean);
	void draw(GLfloat);

	Scene();
	~Scene();
};

