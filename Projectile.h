#pragma once
#include <math.h>

#include "Scene.h"
#include "NewNetworkClient.h"

#define M_PI 3.14f

inline float to_rad(float degrees) {
	return degrees * M_PI / 180.0f;
}

struct ProjectileInformation
{
	bool active;
	unsigned int parent; //Panzer that shot the Projectile
	GLfloat location[2];
	GLfloat rotation;
};

class Projectile
{
private:

	const GLfloat projectileSpeed = 500.0f;

	struct ProjectileInformation projectileInformation;

	GLfloat direction[2];

	GLboolean lastActive;

	ImageSprite* image;

	Scene* scene;

	GLuint* fireTextures;
	GLuint fireTexturesAmount;

	GLuint* explosionTextures;
	GLuint explosionTexturesAmount;

	//Format: 14x9
	GLfloat fireSize[2] = { 56.0f, 36.0f };

	//Format: 20x20
	GLfloat explosionSize[2] = { 80.0f, 80.0f };


	void explode();
public:
	Projectile();
	~Projectile();
	void initProjectile(GLfloat*, GLuint , GLuint*, GLuint, GLuint*, GLuint, Scene*, NetworkClient*, GLuint);
	struct ProjectileInformation* getProjectileInformationPtr();
	void update(GLfloat);
};

