<<<<<<< HEAD

=======
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
#include "../game/Player.h"
#include "../game/Game.h"
#include "ThreadedSocket.h"
>>>>>>> 4f943eb901d92a4b0ce4901128631ab040b5d263

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <thread>
#include <nlohmann/json.hpp>
#include "../game/Joueur.h"
#include "../game/Game.h"
class DefaultMessage;
#include "messages/DefaultMessage.h"

#include "../utils/CrossPlatform.h"
#include "ThreadedSocket.h"
#include "ServerClient.h"
#include "Server.h"

class Client : public ThreadedSocket
{
private:
<<<<<<< HEAD
	Joueur &joueur;
	//Game &game;
=======
	Game* game;
	Player* joueur;
>>>>>>> 4f943eb901d92a4b0ce4901128631ab040b5d263
protected:
	int id;
	char* buffer;
	Server& server;

	void execute_thread() override;

	int recv_message();


public:
<<<<<<< HEAD
	Client(int, Socket, Server&, Joueur &);
=======
	Client(int, Socket, Server&, Game* game);
>>>>>>> 4f943eb901d92a4b0ce4901128631ab040b5d263
	~Client();

	void end_thread();
	const int get_id() const;
	Joueur &get_joueur();


	bool send_message(DefaultMessage &);
};

#endif
