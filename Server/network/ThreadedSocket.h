
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
#include "../utils/Output.h"
#include "../utils/CrossPlatform.h"

#ifndef THREADED_SOCKET_H
#define THREADED_SOCKET_H

class ThreadedSocket
{
protected:
	char* output_prefix;
	const int MAXDATASIZE;
	bool init_winsocks;
	Socket socket_;
	bool is_alive;
	std::thread thread;

	virtual bool close_socket();

	virtual void execute_thread() = 0;


public:
	ThreadedSocket(Socket, bool, const int);
	~ThreadedSocket();

	void start_thread();
	virtual void end_thread();
	void join_thread();

	bool get_is_alive();
};


#endif
