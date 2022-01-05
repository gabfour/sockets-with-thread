#include "DefaultMessage.h"
#include "LoginMessage.h"
#include "../../utils/Output.h"

std::unique_ptr<DefaultMessage> DefaultMessage::handle_message(Client &client, nlohmann::json json) {
	int id = json["id"];
	DefaultMessage* content = nullptr;
	switch (id) {
		case LoginMessage::ID:
			content = new LoginMessage(client, json);
			break;
		default:
			Output::GetInstance()->print_error("[DEFAULT MESSAGE]", "Message unknown %d", id);
			break;
	}
	return std::unique_ptr<DefaultMessage>(content);
}

DefaultMessage::DefaultMessage(Client &client, int id, nlohmann::json json) : id(id), content(this), json(json), client(client) {
}

int DefaultMessage::get_id() {
	return id;
}

DefaultMessage* DefaultMessage::get_content() {
	return content;
}