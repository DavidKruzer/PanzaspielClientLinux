#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ViewModel
{
private:
	glm::mat4 transformationMatrix;
public:
	void viewModelInit(GLfloat*, GLfloat, GLfloat*, GLuint);
	ViewModel();
	~ViewModel();
};

