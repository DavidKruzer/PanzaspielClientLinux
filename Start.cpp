/*
* Start.cpp
*
*  Created on: 28.12.2017
*      Author: David Kruse
*/
#include "stdafx.h"
#include "Game.h"

// Window dimensions
const GLuint WIDTH = 1600, HEIGHT = 800;

#define playerName_Length 20

int playerName_verify(char* playerName)
{
	for (int i = 0; i < playerName_Length; i++)
	{
		if (playerName[i] == '\0')
		{
			if (i > 4)
			{
				return 0;
			}
			printf("Player Name %s too short.\n", playerName);
			return -1;
		}

		if (!(((playerName[i] >= 'a') && (playerName[i] <= 'z')) || ((playerName[i] >= 'A') && (playerName[i] <= 'Z'))))
		{
			printf("Player Name has invalid Characters.\n");
			return -1;
		}

	}
	printf("Player Name has no terminating Character.\n");
	return -1;
}

void glfwError(int id, const char* description)
{
	printf("GLFW Error:\n%s\n", description);
}

int main(void)
{

	NetworkClient netClient;

	InputCollector inputCollector;

	char expectedReply[14] = "Hello Client!";
	char reply[14] = { 0 };

	if (netClient.connectClient() != 0)
	{
		printf("Error connecting with Server.\n");
		return 1;
	}

	printf("Successfully Connected with Server.\n");

	netClient.addMessage(0, reply, sizeof(reply));

	if (netClient.createListener() != 0)
	{
		printf("Problem starting listener Thread.\n");
		return 1;
	}
	printf("Start listening for incoming Messages.\n");


	printf("Please enter your Player Name:\n\t-min. 5, max. 19 characters\n\t-only characters from a/A - z/z\n");
	char playerName[20] = { 0 };
	
	do
	{
		scanf_s("%s", playerName, 20);

		for (int i = 0; i < playerName_Length; i++)
		{
			if (playerName[i] == '\n')
			{
				playerName[i] = '\0';
			}
		}
		playerName[playerName_Length - 1] = '\0';
	} while (playerName_verify(playerName) != 0);

	netClient.sendMessage(0, playerName, 20);
	netClient.addMessage(0, reply, sizeof(reply));
	//Wait for response to Hello

	while (reply[0] == '\0')
	{
		Sleep(100);
	}

	if (strcmp(reply, expectedReply) != 0)
	{
		printf("Hello Reply wrong: %s\n", reply);
		return 1;
	}

	netClient.removeMessage(0);

	printf("Player Name %s confirmed.\n", playerName);


	while (1)
	{
		printf("Press any Key to enter queue, press e to quit!\n");

		fflush(stdin);
		if (getchar() == 'e')
		{
			break;
		}

		struct GameInformation gameInformation = { 0 };
		netClient.addMessage(1, &gameInformation, sizeof(gameInformation));
		netClient.sendMessage(5, NULL, 0);
		printf("Waiting for new Game to start!\n");

		while (gameInformation.playerAmount == 0)
		{
			Sleep(100);
		}

		netClient.removeMessage(1);

		printf("Starting game with %d Players. This is Player %d.\n", gameInformation.playerAmount, gameInformation.myNumber);

		// Init GLFW
		glfwSetErrorCallback(&glfwError);

		if (!glfwInit())
		{
			printf("Problem initialising GLFW!\n");
		}

		// Set all the required options for GLFW
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		// Create a GLFWwindow object that we can use for GLFW's functions
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PANZASPIEL", NULL, NULL);
		glfwMakeContextCurrent(window);
		
		// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
		glewExperimental = GL_TRUE;
		// Initialize GLEW to setup the OpenGL Function pointers
		glewInit();
		
		// Define the viewport dimensions
		glViewport(0, 0, WIDTH, HEIGHT);

		glfwSetKeyCallback(window, InputCollector::key_callback);

		GLfloat screenSize[2] = { WIDTH, HEIGHT };

		Game game(&gameInformation, &netClient, screenSize);
		
		GLdouble lastTime = glfwGetTime();

		// Game loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();

			GLdouble time = glfwGetTime();

			GLfloat passedTime = (GLfloat)(time - lastTime);
			lastTime = time;

			game.update(passedTime);

			// Render
			// Clear the colorbuffer
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			game.draw(passedTime);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		// Terminate GLFW, clearing any resources allocated by GLFW.
		glfwTerminate();
	}

	netClient.disconnect();
}
