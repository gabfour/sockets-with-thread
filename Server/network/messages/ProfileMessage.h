#ifndef PROFILEMESSAGE_H_
#define PROFILEMESSAGE_H_

#include <nlohmann/json.hpp>
#include "DefaultMessage.h"

class ProfileMessage : public DefaultMessage {
public:
	static const int ID = 0;
	ProfileMessage(nlohmann::json json);

private:
	void treat_message() override;
};

#endif