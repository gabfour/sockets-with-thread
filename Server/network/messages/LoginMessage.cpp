#include "LoginMessage.h"
#include "../../utils/Output.h"

LoginMessage::LoginMessage(Client &client, nlohmann::json json) : DefaultMessage(client, ID, json) {

}

void LoginMessage::deserialized() {
	std::string username;
	std::string password;

	try {
		username = json["username"];
		password = json["password"];
	}
	catch (std::exception _) {
		Output::GetInstance()->print_error("LoginMessage", "Error while deserializing: potentially missing json field");
		return;
	}
	Output::GetInstance()->print("Username(", username, "), Password(", password, ")\n");
	if (strcmp(username.c_str(), "admin") == 0 && strcmp(password.c_str(), "admin") == 0) {
		response_message = "Connected successfully";
	}
	else {
		response_message = "Conenction failed";
	}
	Output::GetInstance()->print("Sending reponse...\n");
	if (client.send_message(serialized())) {
		Output::GetInstance()->print("Sended\n");
	}
}

nlohmann::json LoginMessage::serialized() {
	nlohmann::json json;

	json["id"] = ID;
	json["message"] = response_message;

	return json;
}