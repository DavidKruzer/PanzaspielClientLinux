#pragma once
#include "Panzer.h"


#define maxProjectiles 100

#define updateRate 50 //update network 50 times a second

struct GameInformation
{
	unsigned int myNumber;
	unsigned int playerAmount;
};


struct GameFinishInformation
{
	int type;
	int winner;
	char playerName[20];
};

class Game
{
private:
	Scene scene;
	PlayerPanzer panzer;
	OnlinePanzer* onlinePanzer;
	Projectile projectiles[maxProjectiles];
	GLuint otherPanzerAmount;
	GLuint projectileCount = 0;
	GLuint projectileTexture;
	GLfloat projectileSize[2] = { 30.0f, 10.0f };
	unsigned int playerAmount;
	unsigned int myNumber;
	GLuint* fireTextures;
	GLuint fireTexturesAmount;
	struct GameFinishInformation gameFinishInfo;
	ViewModel viewModel;

	GLuint* explosionTextures;
	GLuint explosionTexturesAmount;


	unsigned int lastProjectileCount = 0;

	GLfloat totalTime = 0;

	int lastUpdateDiv = 0;

public:
	Game(struct GameInformation*, NetworkClient*, GLfloat*);
	~Game();
	void draw(GLfloat);
	void update(GLfloat);
};

