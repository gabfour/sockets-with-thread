#ifndef CROSSPLATFORM_H_
#define CROSSPLATFORM_H_

#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _WIN32

	#include <winsock2.h>
	#include <Windows.h>
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

#ifdef _WIN32
using Socket = SOCKET;
using Address = SOCKADDR_IN;

#else
using Socket = int;
using Address = struct sockaddr_in;
#endif

#endif