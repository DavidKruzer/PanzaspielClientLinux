#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TextureManager.h"

class ImageSprite
{
private:
	GLfloat* location;

	GLfloat* size;

	GLfloat* rotation;

	GLfloat drawnRotation;

	const GLfloat vertices[32] = {
		// Positions          // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // Top Left
	};

	const GLuint indices[6] = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};

	glm::mat4 transformationMatrix;

	GLuint VBO, VAO, EBO;

	bool visibleTrue = GL_TRUE;

	TextureManager* textureManager;
public:
	bool* visible;
	GLuint texture;

	ImageSprite();
	~ImageSprite();
	void initImageSprite(GLuint, GLfloat*, GLfloat*, GLfloat*, TextureManager*);
	void draw(GLuint);
};

