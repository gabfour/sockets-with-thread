#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#define _CRT_SECURE_NO_WARNINGS
#endif
#include "Client.h"
#include "../utils/Output.h"
#include "messages/DefaultMessage.h"

Client::Client(int id, Socket socket, Server& server) : ThreadedSocket(socket, false, MAXDATASIZE), id(id), server(server)
{
	buffer = new char[MAXDATASIZE];

	char numstr[21]; // enough to hold all numbers up to 64-bits
	sprintf(numstr, "%d", id);
	std::string prefix = std::string(std::string(std::string("[CLIENT_") + numstr + std::string("] ")));
	output_prefix = (char*)malloc(strlen(prefix.c_str()) + 1);
	if (!output_prefix) return;
	strcpy(output_prefix, prefix.c_str());
}

Client::~Client()
{
	ThreadedSocket::~ThreadedSocket();
	delete[] buffer;
	free(output_prefix);
}

bool Client::send_message(const nlohmann::json &json)
{
	if (socket_ == NULL || !is_alive)
		return false;
	std::string json_str = json.dump();
	const char* buffer = json_str.c_str();
	if (send(socket_, buffer, (int)strlen(buffer), 0) == -1) {
		Output::GetInstance()->print_error(output_prefix, "Error while sending message to client ");
		return false;
	}

	return true;
}
int Client::recv_message()
{
	if (socket_ == NULL || !is_alive)
		return -1;

	int length;
	if ((length = recv(socket_, buffer, MAXDATASIZE, 0)) == -1) {
		Output::GetInstance()->print_error(output_prefix, "Error while receiving message from client ");
		return length;
	}

	// Suppression des retours chariots (\n et \r)
	while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r'))
		length--;
	// Ajout de backslash zero a la fin pour en faire une chaine de caracteres
	if (length >= 0 && length < MAXDATASIZE)
		buffer[length] = '\0';

	return length;
}

void Client::end_thread()
{
	if (!is_alive)
		return;

	// Sending close connection to client
	send_message("CONNECTION_CLOSED");

	ThreadedSocket::end_thread();
}

void Client::execute_thread()
{
	int length;
	time_t time_value;
	struct tm* time_info;

	Output::GetInstance()->print(output_prefix, "Thread client starts with id=", id, ".\n");

	// Boucle infinie pour le client
	while (server.get_is_running()) {

		if (socket_ == NULL || !is_alive || !server.get_is_running())
			return;

		// On attend un message du client
		if ((length = recv_message()) == -1) {
			break;
		}

		if (socket_ == NULL || !is_alive || !server.get_is_running())
			return;

		// Affichage du message
		Output::GetInstance()->print(output_prefix, "Message received : ", buffer, "\n");
		nlohmann::json json;
		try {
			json = nlohmann::json::parse(std::string(buffer));
		}
		catch (std::exception e) {
			Output::GetInstance()->print_error(output_prefix, (std::string("Message is not parsable as JSON: ") + std::string(buffer)).c_str());
			continue;
		}
		
		std::unique_ptr<DefaultMessage> message = DefaultMessage::handle_message(*this, json);
		if (message.get() == nullptr) {
			Output::GetInstance()->print_error(output_prefix, "Message not found or not allocated");
			continue;
		}
		Output::GetInstance()->print(output_prefix, "Message ", message->get_id(), " found\n");
		message->deserialized();

		//if (strcmp(buffer, "DISCONNECT") == 0) {
		//	break;
		//}
		//else {
		//	// On recupere l'heure et la date
		//	time(&time_value);
		//	time_info = localtime(&time_value);

		//	// Traitement du message reçu
		//	if (strcmp(buffer, "DATE") == 0)
		//		strftime(buffer, MAXDATASIZE, "%e/%m/%Y", time_info);
		//	else if (strcmp(buffer, "DAY") == 0)
		//		strftime(buffer, MAXDATASIZE, "%A", time_info);
		//	else if (strcmp(buffer, "MONTH") == 0)
		//		strftime(buffer, MAXDATASIZE, "%B", time_info);
		//	else
		//		sprintf(buffer, "%s is not recognized as a valid command", buffer);

		//	if (socket == NULL || !is_alive)
		//		return;

		//	// On envoie le buffer
		//	Output::GetInstance()->print(output_prefix, "Sending message \"", buffer, "\" to client...\n");
		//	if (!send_message(buffer)) {
		//		break;
		//	}

		//	Output::GetInstance()->print(output_prefix, "Message \"", buffer, "\" send to client successfully.\n");
		//}
	}
	server.client_disconnteced(*this);

	end_thread();
}


const int Client::get_id() const {
	return id;
}