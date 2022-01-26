#ifndef DEFAULTMESSAGE_H_
#define DEFAULTMESSAGE_H_

#include "../Client.h"
#include <nlohmann/json.hpp>

class DefaultMessage {
public:
	static std::unique_ptr<DefaultMessage> handle_message(Client &client, nlohmann::json json);

	DefaultMessage(Client &client, int id, nlohmann::json json);

	int get_id();
	DefaultMessage*get_content();

	virtual void deserialized() = 0;
	virtual nlohmann::json serialized() = 0;
protected:
	int id;
	Client& client;
	DefaultMessage *content;
	nlohmann::json json;

};

#endif