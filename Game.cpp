#include "stdafx.h"
#include "Game.h"

/*
* Game.cpp
*
*  Created on: 04.01.2018
*      Author: david
*/

Game::~Game()
{
}

Game::Game(struct GameInformation* gameInformation, NetworkClient* netClient, GLfloat* screenSize)
{

	gameFinishInfo.type = 0;

	playerAmount = gameInformation->playerAmount;
	myNumber = gameInformation->myNumber;

	otherPanzerAmount = playerAmount - 1;


	scene.init();

	GLuint backgroundTexture = scene.textureManager->addTexture("Textures\\DesertBackground.png");

	scene.setBackground(screenSize, backgroundTexture);

	GLfloat cameraLocation[2] = { 0.0f, 0.0f };
	viewModel.viewModelInit(cameraLocation, 0.0, screenSize, scene.program);

	GLuint texture1 = scene.textureManager->addTexture("Textures\\Panzer1.png");
	GLuint destroyedTexture1 = scene.textureManager->addTexture("Textures\\Panzer1destroyed.png");
	GLuint texture2 = scene.textureManager->addTexture("Textures\\Panzer2.png");
	GLuint destroyedTexture2 = scene.textureManager->addTexture("Textures\\Panzer2destroyed.png");


	projectileTexture = scene.textureManager->addTexture("Textures\\Shot.png");

	fireTexturesAmount = 5;
	fireTextures = new GLuint[5]{ scene.textureManager->addTexture("Textures\\Fire1.png"),scene.textureManager->addTexture("Textures\\Fire2.png"),scene.textureManager->addTexture("Textures\\Fire3.png"),scene.textureManager->addTexture("Textures\\Fire4.png"),scene.textureManager->addTexture("Textures\\Fire5.png") };

	explosionTexturesAmount = 6;
	explosionTextures = new GLuint[6]{ scene.textureManager->addTexture("Textures\\Explosion1.png"), scene.textureManager->addTexture("Textures\\Explosion2.png"), scene.textureManager->addTexture("Textures\\Explosion3.png"), scene.textureManager->addTexture("Textures\\Explosion4.png"),scene.textureManager->addTexture("Textures\\Explosion5.png"), scene.textureManager->addTexture("Textures\\Explosion6.png") };

	GLfloat loc[2] = { 100.0f, 100.0f };
	GLfloat siz[2] = { 100.0f, 60.0f };

	panzer.initPlayerPanzer(loc, 0.0f, siz, texture1, destroyedTexture1, &scene, netClient, gameInformation->myNumber);

	//Create Array, which stores Panzer, that are sent by the server
	onlinePanzer = new OnlinePanzer[otherPanzerAmount];

	netClient->addMessage(70, &gameFinishInfo, sizeof(gameFinishInfo));

	for (GLuint i = 0; i < otherPanzerAmount; i++)
	{
		onlinePanzer[i].initOnlinePanzer(loc, 0.0f, siz, texture2, destroyedTexture2, &scene, netClient, i + (i >= myNumber));
	}

	for (unsigned int i = 0; i < maxProjectiles; i++)
	{
		projectiles[i].initProjectile(projectileSize, projectileTexture, fireTextures, fireTexturesAmount, explosionTextures, explosionTexturesAmount, &scene, netClient, i);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Game::draw(GLfloat passedTime)
{
	scene.draw(passedTime);
}

void Game::update(GLfloat passedTime)
{
	//Passed Time in Seconds
	if (gameFinishInfo.type == 0)
	{
		totalTime += passedTime;

		panzer.updateControl(passedTime);

		if (lastUpdateDiv != (int)(totalTime * updateRate))
		{
			panzer.sendPanzerInfo();
			lastUpdateDiv = (int)(totalTime * updateRate);
		}

		for (unsigned int i = 0; i < otherPanzerAmount; i++)
		{
			onlinePanzer[i].updatePrediction(passedTime);
		}

		for (unsigned int i = 0; i < maxProjectiles; i++)
		{
			projectiles[i].update(passedTime);
		}
	}

	else
	{
		//Game is finished
		if (gameFinishInfo.type == 2)
		{
			printf("Player %s won!\n", gameFinishInfo.playerName);
		}
	}
}
