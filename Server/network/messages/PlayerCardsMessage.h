#ifndef PLAYER_CARDS_MESSAGE_H_
#define PLAYER_CARDS_MESSAGE_H_


#include <nlohmann/json.hpp>
#include <memory>
#include <list>

#include "../Client.h"
#include "../../game/Carte.h"
#include "DefaultMessage.h"

class PlayerCardsMessage : public DefaultMessage {
public:
	static const int ID = 1;
	PlayerCardsMessage(Client& client, nlohmann::json json);
	static void send_message(Client &client, std::list<std::unique_ptr<Carte>> &cards);

	void deserialized() override;
	nlohmann::json serialized() override;
private:
	const char* TAG = "[PlayerCardsMessage] ";

	std::list<std::unique_ptr<Carte>>* cards;
};

#endif