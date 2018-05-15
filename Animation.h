#pragma once
#include "ImageSprite.h"


class Animation
{

private:
	ImageSprite imageSprite;
	GLuint* textures;
	GLuint textureAmount;

	GLfloat timePerTexture;
	GLfloat timeFromStart;
	GLboolean loop;
	GLfloat location[2];
	GLfloat size[2];
	GLfloat rotation;
public:
	Animation();
	~Animation();
	void newAnimation(GLfloat*, GLfloat*, GLfloat, GLfloat, GLuint*, GLuint, GLboolean, TextureManager*);
	GLboolean draw(GLfloat, GLuint);
};