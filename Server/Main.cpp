#include "utils/Output.h"
#include "utils/Utils.h"
#include "network/Server.h"
#include "network/Config.h"
#include "services/GameService.h"

#include <nlohmann/json.hpp>

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
		Output::GetInstance()->print_error("Invalid parameters !");
		Output::GetInstance()->print_error("program usage : ", argv[0], " connection_port");
		exit(EXIT_FAILURE);
	}

	GameService::get_instance().init();

	std::unique_ptr<Server> server(Server::create_server(port));
	server->start();

	start_commands(*server);

	server->join_thread();
	return EXIT_SUCCESS;

}
