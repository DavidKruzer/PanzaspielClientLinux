#include "stdafx.h"
#include "Projectile.h"

/*
* Projectile.cpp
*
*  Created on: 03.01.2018
*      Author: david
*/

Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}

void Projectile::initProjectile(GLfloat* size, GLuint texture, GLuint* fireTextures, GLuint fireTexturesAmount, GLuint* explosionTextures, GLuint explosionTexturesAmount, Scene* scene, NetworkClient* netClient, GLuint number)
{
	projectileInformation.active = false;
	image = scene->addImageSprite(texture, this->projectileInformation.location, size, &this->projectileInformation.rotation);
	image->visible = &projectileInformation.active;
	this->scene = scene;
	this->fireTextures = fireTextures;
	this->fireTexturesAmount = fireTexturesAmount;
	this->explosionTextures = explosionTextures;
	this->explosionTexturesAmount = explosionTexturesAmount;

	netClient->addMessage(1000 + number, &projectileInformation, sizeof(projectileInformation));
}

struct ProjectileInformation* Projectile::getProjectileInformationPtr()
{
	return &projectileInformation;
}

void Projectile::update(GLfloat passedTime)
{
	if (!lastActive && projectileInformation.active)
	{
		direction[0] = -cos(to_rad(projectileInformation.rotation)) * projectileSpeed;
		direction[1] = sin(to_rad(projectileInformation.rotation)) * projectileSpeed;

		scene->addAnimation(fireTextures, fireTexturesAmount, projectileInformation.location, fireSize, projectileInformation.rotation, GL_FALSE);
		lastActive = GL_TRUE;
	}
	else if (lastActive && !projectileInformation.active)
	{
		explode();
	}

	if (projectileInformation.active)
	{
		projectileInformation.location[0] += direction[0] * passedTime;
		projectileInformation.location[1] += direction[1] * passedTime;
	}
}

void Projectile::explode()
{
	scene->addAnimation(explosionTextures, explosionTexturesAmount, projectileInformation.location, explosionSize, projectileInformation.rotation, GL_FALSE);
	lastActive = GL_FALSE;
}
