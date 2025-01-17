#ifndef SERVER_H_
#define SERVER_H_

#include "../utils/CrossPlatform.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <cstdarg>
#include <list>


#include "../utils/Semaphore.h"
#include "Client.h"
#include "../utils/Output.h"
#include "ServerClient.h"
#include "Client.h"
#include "Config.h"


class Server : public ThreadedSocket {
public:
	Server(Socket);
	~Server();

	static Server* create_server(int port);

	void start();
	void stop();

	void client_disconnected(Client& client);

	bool get_is_running();
private:
	Game* game;
	std::unique_ptr<std::thread> _runningThread;

	bool is_running;

	std::list<std::unique_ptr<Client>> clients;

	static Socket open_connection(int);
	Socket accept_connection(Socket);
protected:
	void execute_thread();
};

#endif