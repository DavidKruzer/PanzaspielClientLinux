#pragma once
#include <WS2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define PORTNUM "2300"

#define bufferLength 1000

#define maxType 2000

struct NetworkMessage
{
	unsigned int size;
	void* saveLocation;
};

struct NetworkEvent
{
	void (*functionPtr)(void);
};

class NetworkClient
{
private:
	SOCKET ConnectSocket = INVALID_SOCKET;
	int hallo = 10;
	struct NetworkMessage networkMessages[maxType];
	struct NetworkEvent networkEvents[maxType];

public:
	NetworkClient();
	~NetworkClient();
	int connectClient();
	int sendMessage(unsigned int, void*, int);
	void addMessage(int, void*, int);
	void removeMessage(int);
	void disconnect();
	int createListener();
	void addEvent(unsigned int, void(*)());
	void removeEvent(unsigned int);
	static DWORD WINAPI ThreadFunc(void*);
};

