#include "stdafx.h"
#include "ViewModel.h"

/*
* ViewModel.cpp
*
*  Created on: 28.12.2017
*      Author: David Kruse
*/

ViewModel::ViewModel()
{
}


ViewModel::~ViewModel()
{
}


void ViewModel::viewModelInit(GLfloat* location, GLfloat rotation, GLfloat* shownSize, GLuint program)
{
	transformationMatrix = glm::mat4(1.0f);
	transformationMatrix = glm::scale(transformationMatrix, glm::vec3(2 / shownSize[0], 2 / shownSize[1], 1));

	GLuint cameraTransformationLoc = glGetUniformLocation(program, "cameraTransformation");
	glUniformMatrix4fv(cameraTransformationLoc, 1, GL_FALSE, glm::value_ptr(transformationMatrix));
}

