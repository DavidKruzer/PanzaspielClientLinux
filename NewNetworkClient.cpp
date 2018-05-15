#include "stdafx.h"
#include "NewNetworkClient.h"


NetworkClient::NetworkClient()
{
}


NetworkClient::~NetworkClient()
{
}

void NetworkClient::disconnect()
{

}

int NetworkClient::connectClient()
{
	WSADATA wsaData;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSA Startup failed!\n");
		return -1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	printf("Server IP eingeben:\n");
	char serverIP[100];
	scanf_s("%s", serverIP, 100);

	iResult = getaddrinfo(serverIP, PORTNUM, &hints, &result);
	if (iResult != 0)
	{
		printf("Get addrInfo failed.\n");
		return -1;
	}

	ptr = result;

	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error connecting Socket!\n");
		return -1;
	}

	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

	if (iResult != 0)
	{
		printf("Error connecting to Server.\n");
		return -1;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error connecting to Server.\n");
		return -1;
	}

	printf("Client connected!\n");
	return 0;
}

int NetworkClient::sendMessage(unsigned int type, void* message, int size)
{
	char* buffer = new char[size + sizeof(type)];
	memcpy(buffer, &type, sizeof(type));
	memcpy(&buffer[sizeof(type)], message, size);
	send(ConnectSocket, buffer, size + sizeof(type), 0);
	delete buffer;
	return 0;
}

void NetworkClient::addEvent(unsigned int type, void (*functionPtr)())
{
	networkEvents[type].functionPtr = functionPtr;
}

void NetworkClient::removeEvent(unsigned int type)
{
	networkEvents[type].functionPtr = NULL;
}

void NetworkClient::addMessage(int type, void* location, int length)
{
	if (type >= maxType)
	{
		printf("Message type too high!\n");
		return;
	}
	networkMessages[type].saveLocation = location;
	networkMessages[type].size = length;
}

void NetworkClient::removeMessage(int type)
{
	if (type >= maxType)
	{
		printf("Message type too high!\n");
		return;
	}
	networkMessages[type].saveLocation = NULL;
	networkMessages[type].size = 0;
}

int NetworkClient::createListener()
{
	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, this, 0, NULL);
	return 0;
}

DWORD WINAPI NetworkClient::ThreadFunc(void* data)
{
	NetworkClient* parent = (NetworkClient*) data;
	char buffer[1024];
	while (1)
	{
		int length = recv(parent->ConnectSocket, buffer, sizeof(buffer), 0);

		unsigned int messageType;

		for (int locInBuf = 0; locInBuf < length - sizeof(messageType);)
		{
			messageType = *((unsigned int*)&buffer[locInBuf]);
			if (messageType > maxType)
			{
				printf("Wrong Message Type: %d\n", messageType);
				break;
			}
			if (parent->networkMessages[messageType].size == 0)
			{
				//Wrong MessageType received
				//printf("Wrong Message Type: %d\n", messageType);
				break;
			}

			//printf("Message %d received.\n", messageType);

			locInBuf += sizeof(messageType);


			//remaining buffer must be bigger or equal the requested Size
			if (length - locInBuf >= parent->networkMessages[messageType].size)
			{
				//Copy message from buffer to desired destination
				//printf("Message %d successfully received. Content: %s\n", messageType, &buffer[locInBuf]);
				memcpy(parent->networkMessages[messageType].saveLocation, &buffer[locInBuf], parent->networkMessages[messageType].size);
				locInBuf += parent->networkMessages[messageType].size;
				if (parent->networkEvents[messageType].functionPtr != NULL)
				{
					parent->networkEvents[messageType].functionPtr();
				}
			}
			else
			{
				printf("Problem receiving Information\n");
				break;
			}
		}
	}

	return 0;
}