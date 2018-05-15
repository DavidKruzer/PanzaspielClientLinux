#include "stdafx.h"
#include "ImageSprite.h"

/*
* ImageSprite.cpp
*
*  Created on: 28.12.2017
*      Author: David Kruse
*/

ImageSprite::ImageSprite()
{
}


ImageSprite::~ImageSprite()
{
}

void ImageSprite::initImageSprite(GLuint texture, GLfloat* location, GLfloat* size, GLfloat* rotation, TextureManager* textureManager)
{
	this->texture = texture;
	this->location = location;
	this->size = size;
	this->rotation = rotation;
	this->textureManager = textureManager;
	visible = &visibleTrue;
	drawnRotation = 491827.8f;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void ImageSprite::draw(GLuint program)
{
	// Draw container
	if (*visible)
	{
		//Check weather rotation changed
		if (*rotation != drawnRotation)
		{
			drawnRotation = *rotation;

			transformationMatrix = glm::mat4(1.0f);

			transformationMatrix = glm::scale(transformationMatrix, glm::vec3(size[0], size[1], 1.0f));

			transformationMatrix = glm::rotate(transformationMatrix, glm::radians(*rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		}

		transformationMatrix[0].w = location[0];
		transformationMatrix[1].w = location[1];

		GLuint transformationLoc = glGetUniformLocation(program, "spriteTransformation");
		glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));;


		GLuint sizeLoc = glGetUniformLocation(program, "size");
		glUniform2f(sizeLoc, size[0], size[1]);

		textureManager->useTexture(texture);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}