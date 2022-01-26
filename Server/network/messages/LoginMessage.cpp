#include "LoginMessage.h"
#include "../../utils/Output.h"
#include "../../game/Player.h"
#include "PlayerCardsMessage.h"

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
	client.get_player().set_name(username);
	response_message = username;
	client.send_message(*this);
	PlayerCardsMessage::send_message(client, client.get_player().get_cards());
}

nlohmann::json LoginMessage::serialized() {
	nlohmann::json json;

	json["username"] = response_message;

	return json;
}