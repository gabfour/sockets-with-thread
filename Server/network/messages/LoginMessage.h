#ifndef PROFILEMESSAGE_H_
#define PROFILEMESSAGE_H_

#include "../Client.h"
#include <nlohmann/json.hpp>
#include "DefaultMessage.h"

class LoginMessage : public DefaultMessage {
public:
	static const int ID = 0;
	LoginMessage(Client &client, nlohmann::json json);

	void deserialized() override;
	nlohmann::json serialized() override;
private:
	const char *TAG = "[LoginMessage] ";

	std::string response_message;
};

#endif