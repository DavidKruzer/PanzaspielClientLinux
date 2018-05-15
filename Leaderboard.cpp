#pragma once
#include "NewNetworkClient.h"

struct LeaderboardInformation
{
	int position;
	char playerName[20];
	int points;
};

struct LeaderboardInformation* requestInformation = NULL;

NetworkClient* netClient;

void leaderboard_GetAroundMe()
{

	if (requestInformation == NULL)
	{
		requestInformation = new struct LeaderboardInformation[20];
	}

	netClient->addEvent(60, &leaderboard_GetAroundMeReceived);
	netClient->addMessage(60, requestInformation, sizeof(struct LeaderboardInformation));

}


void leaderboard_GetAroundMeReceived()
{
	netClient->removeMessage(60);
	netClient->removeEvent(60);
	delete requestInformation;
	requestInformation = NULL;
}