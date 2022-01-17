#include "LoginMessage.h"
#include "../../utils/Output.h"

LoginMessage::LoginMessage(Client &client, nlohmann::json json) : DefaultMessage(client, ID, json) {

}

void LoginMessage::deserialized() {
	std::string username;

	try {
		username = json["username"];
	}
	catch (std::exception _) {
		Output::GetInstance()->print_error(TAG, "Error while deserializing: potentially missing json field");
		return;
	}
	Output::GetInstance()->print_debug(TAG, "<- Username(", username, ")\n");
	client.get_joueur().set_name(username);
	response_message = username;
	client.send_message(*this);
}

nlohmann::json LoginMessage::serialized() {
	nlohmann::json json;

	json["username"] = response_message;

	return json;
}