#pragma once
#include "Scene.h"
#include "InputCollector.h"
#include "Projectile.h"

#define maxHealth 4

struct PanzerInformation
{
	unsigned int id; //id of object
	float location[2];
	float rotation;
	int movement; //Bit 0: Farwards, Bit 1: Backwards, Bit2: Right, Bit3: Left
	int health;
};

class Panzer
{
protected:
	struct PanzerInformation panzerInformation;
	GLfloat size[2];
	GLfloat direction[2]; //Direction the Panzer looks in
	ImageSprite* image;
	GLfloat lastRotation = 10000;
	GLuint texture;
	GLuint destroyedTexture;
	const GLfloat speed = 150;
	const GLfloat turnSpeed = 150;

	const GLfloat startLocation[4][2] = { { 400, 200 },{ -400, -200 },{ 400, -200 },{ -400, 200 } };
	const GLfloat startRotation[4] = { 26.5f, -153.4f, -26.5f, 135.4f };

	void initPanzer(GLfloat*, GLfloat, GLfloat*, GLuint, GLuint, Scene*, unsigned int);
	void newRotation();
	void update(GLfloat);
	void enterStartPosition(int);
public:
	Panzer();
	~Panzer();
};


class PlayerPanzer : Panzer
{
private:
	NetworkClient* netClient;
	int forwardKey = GLFW_KEY_UP;
	int leftKey = GLFW_KEY_LEFT;
	int backwardsKey = GLFW_KEY_DOWN;
	int rightKey = GLFW_KEY_RIGHT;
	int fireKey = GLFW_KEY_SPACE;
	GLfloat canonCooldown = 0.0f;
	const GLfloat fireOffset = 75.0f;
public:
	void initPlayerPanzer(GLfloat*, GLfloat, GLfloat*, GLuint, GLuint, Scene*, NetworkClient*, unsigned int);
	void updateControl(GLfloat);
	void sendPanzerInfo();
	void sendNewProjectile();
};

class OnlinePanzer : Panzer
{
public:
	void initOnlinePanzer(GLfloat*, GLfloat, GLfloat*, GLuint, GLuint, Scene*, NetworkClient*, int);
	void updatePrediction(GLfloat);
};