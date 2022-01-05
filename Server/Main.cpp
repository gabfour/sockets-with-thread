#include "utils/Output.h"
#include "network/Server.h"
#include "network/Config.h"
//#include <nlohmann/json.hpp>

bool strtoi(char*, int*);

#ifdef WIN32

void sleep(DWORD dwMilliseconds)
{
	Sleep(dwMilliseconds * 1000);
}
void usleep(DWORD dwMilliseconds)
{
	Sleep(dwMilliseconds);
}

#endif

static void start_commands(Server& server) {
	while (true) {
		char buffer[MAXDATASIZE];
		std::cin >> buffer;

		if (strcmp(buffer, "EXIT") == 0 && Output::GetInstance()->confirm_exit()) {
			server.stop();
			server.end_thread();
			break;
		}
		else {
			Output::GetInstance()->print("[MAIN] ", buffer, " is not recognized as a valid command", "\n");
		}
	}
}

int main(int argc, char* argv[])
{
	Output::GetInstance()->print("*********************************************************\n");
	Output::GetInstance()->print("*                      6 qui prend                      *\n");
	Output::GetInstance()->print("*********************************************************\n");
	Output::GetInstance()->print("\n");
	Output::GetInstance()->print("\n");

	// Lecture des paramètres en cours
	int port;
	if (argc != 2 || !strtoi(argv[1], &port)) {
		Output::GetInstance()->print("Invalid parameters !");
		Output::GetInstance()->print("program usage : ", argv[0], " connection_port");
		exit(EXIT_FAILURE);
	}

	std::unique_ptr<Server> server(Server::create_server(port));
	server->start();

	start_commands(*server);

	server->join_thread();
	return EXIT_SUCCESS;

}


bool strtoi(char* value, int* result)
{
	char* p;
	errno = 0;
	long arg = strtol(value, &p, 10);
	if (*p != '\0' || errno != 0) {
		return false;
	}
	if (arg < INT_MIN || arg > INT_MAX) {
		return false;
	}
	*result = arg;
	return true;
}