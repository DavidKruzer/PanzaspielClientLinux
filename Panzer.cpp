#include "stdafx.h"
#include "Panzer.h"

/*
* Panzer.cpp
*
*  Created on: 30.12.2017
*      Author: david
*/

Panzer::Panzer()
{
}


Panzer::~Panzer()
{
}

//General Panzer

void Panzer::enterStartPosition(int panzerNumber)
{
	panzerInformation.location[0] = startLocation[panzerNumber][0];
	panzerInformation.location[1] = startLocation[panzerNumber][1];
	panzerInformation.rotation = startRotation[panzerNumber];
	newRotation();
}

void Panzer::initPanzer(GLfloat* location, GLfloat rotation, GLfloat* size, GLuint texture, GLuint destroyedTexture, Scene *scene, unsigned int id)
{
	panzerInformation.location[0] = location[0];
	panzerInformation.location[1] = location[1];
	this->size[0] = size[0];
	this->size[1] = size[1];
	panzerInformation.rotation = rotation;
	panzerInformation.id = id;

	this->texture = texture;
	this->destroyedTexture = destroyedTexture;
	enterStartPosition(id);
	image = scene->addImageSprite(texture, panzerInformation.location, this->size, &panzerInformation.rotation);
}

void Panzer::newRotation()
{
	direction[0] = -cos(to_rad(panzerInformation.rotation));
	direction[1] = sin(to_rad(panzerInformation.rotation));
}

void Panzer::update(GLfloat timePassed)
{
	if (panzerInformation.health > 0)
	{
		image->texture = texture;
		if (lastRotation != panzerInformation.rotation)
		{
			newRotation();
			lastRotation = panzerInformation.rotation;
		}

		if (panzerInformation.movement & 0x01) //Forwards
		{
			panzerInformation.location[0] += direction[0] * timePassed * speed;
			panzerInformation.location[1] += direction[1] * timePassed * speed;
		}

		if (panzerInformation.movement & 0x02) //Backwards
		{
			panzerInformation.location[0] -= direction[0] * timePassed * speed;
			panzerInformation.location[1] -= direction[1] * timePassed * speed;
		}

		if (panzerInformation.movement & 0x04) //Right
		{
			panzerInformation.rotation -= timePassed * turnSpeed;
		}

		if (panzerInformation.movement & 0x08) //Left
		{
			panzerInformation.rotation += timePassed * turnSpeed;
		}
	}
	else
	{
		//Panzer destroyed
		image->texture = destroyedTexture;
	}
}

// PLAYER PANZER

void PlayerPanzer::initPlayerPanzer(GLfloat* location, GLfloat rotation, GLfloat* size, GLuint texture, GLuint destroyedTexture, Scene *scene, NetworkClient* netClient, unsigned int number)
{
	initPanzer(location, rotation, size, texture, destroyedTexture, scene, number);

	this->netClient = netClient;
	this->panzerInformation.health = maxHealth;

	netClient->addMessage(50, &panzerInformation.health, sizeof(panzerInformation.health));
}

void PlayerPanzer::updateControl(GLfloat timePassed)
{
	if (canonCooldown > 0)
	{
		canonCooldown -= timePassed;
	}
	panzerInformation.movement = 0;
	if (InputCollector::isPressed(forwardKey))
	{
		panzerInformation.movement |= 0x01;
	}
	if (InputCollector::isPressed(backwardsKey))
	{
		panzerInformation.movement |= 0x02;
	}
	if (InputCollector::isPressed(leftKey))
	{
		panzerInformation.movement |= 0x04;
	}
	if (InputCollector::isPressed(rightKey))
	{
		panzerInformation.movement |= 0x08;
	}
	if (InputCollector::isPressed(fireKey))
	{
		if (canonCooldown <= 0)
		{
			sendNewProjectile();
			canonCooldown = 1.0f;
		}
	}

	update(timePassed);
}

void PlayerPanzer::sendPanzerInfo()
{
	netClient->sendMessage(99, &panzerInformation, sizeof(panzerInformation));
}

void PlayerPanzer::sendNewProjectile()
{
	struct ProjectileInformation projectileInformation;
	projectileInformation.parent = panzerInformation.id;
	projectileInformation.location[0] = panzerInformation.location[0] + direction[0] * fireOffset;
	projectileInformation.location[1] = panzerInformation.location[1] + direction[1] * fireOffset;
	projectileInformation.rotation = panzerInformation.rotation;
	projectileInformation.active = true;
	netClient->sendMessage(98, &projectileInformation, sizeof(projectileInformation));
}


// ONLINE PANZER
void OnlinePanzer::initOnlinePanzer(GLfloat* location, GLfloat rotation, GLfloat* size, GLuint texture, GLuint destroyedPanzer, Scene *scene, NetworkClient* netClient, int number)
{
	initPanzer(location, rotation, size, texture, destroyedPanzer, scene, number);
	netClient->addMessage(100 + number, &panzerInformation, sizeof(panzerInformation));
}

void OnlinePanzer::updatePrediction(GLfloat passedTime)
{
	update(passedTime);
}
