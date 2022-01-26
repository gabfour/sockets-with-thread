#ifndef LOGIN_MESSAGE_H_
#define LOGIN_MESSAGE_H_

#include <nlohmann/json.hpp>

#include "DefaultMessage.h"
#include "../Client.h"

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