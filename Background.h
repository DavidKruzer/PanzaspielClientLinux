#pragma once
#include "ImageSprite.h"
class Background
{
private:
	ImageSprite imageSprite;
	GLfloat size[2];
	GLfloat location[2];
	GLfloat rotation;
public:
	Background();
	~Background();
	void init(GLuint, GLfloat*, TextureManager*);
	void draw(GLuint);
};

