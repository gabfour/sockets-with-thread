

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
	Joueur &joueur;
	//Game &game;
protected:
	int id;
	char* buffer;
	Server& server;

	void execute_thread() override;

	int recv_message();


public:
	Client(int, Socket, Server&, Joueur &);
	~Client();

	void end_thread();
	const int get_id() const;
	Joueur &get_joueur();


	bool send_message(DefaultMessage &);
};

#endif
