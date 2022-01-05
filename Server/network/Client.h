#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <thread>
#include "../game/Joueur.h"
#include "../game/Game.h"
#include "ThreadedSocket.h"

#ifndef CLIENT_H
#define CLIENT_H

#include "ThreadedSocket.h"
#include "ServerClient.h"
#include "Server.h"

class Client : public ThreadedSocket
{
private:
	Joueur *joueur;
	Game *game;
protected:
	int id;
	char* buffer;
	Server& server;

	void execute_thread();

	bool send_message(const char*);
	int recv_message();


public:
	Client(int, Socket, Server&, Game* game);
	~Client();

	void start_thread();
	void end_thread();
	void join_thread();
	const int get_id() const;
};

#endif
