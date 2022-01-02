#include "DefaultMessage.h"
#include "ProfileMessage.h"
#include "../../utils/Output.h"

std::unique_ptr<DefaultMessage> DefaultMessage::handle_message(nlohmann::json json) {
	int id = json["id"];
	DefaultMessage* content = nullptr;
	switch (id) {
		case ProfileMessage::ID:
			content = new ProfileMessage(json);
			break;
		default:
			Output::GetInstance()->print_error("[DEFAULT MESSAGE]", "Message unknown %d", id);
			break;
	}
	if (content != nullptr) {
		content->treat_message();
	}
	return std::unique_ptr<DefaultMessage>(content);
}

DefaultMessage::DefaultMessage(int id, nlohmann::json json) : id(id), content(this), json(json) {
}

int DefaultMessage::get_id() {
	return id;
}

DefaultMessage* DefaultMessage::get_content() {
	return content;
}