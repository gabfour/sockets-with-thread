#include "PlayerCardsMessage.h"
#include "../../utils/Output.h"

PlayerCardsMessage::PlayerCardsMessage(Client& client, nlohmann::json json) : DefaultMessage(client, ID, json), cards(nullptr) {

}

void PlayerCardsMessage::send_message(Client& client, std::list<std::unique_ptr<Carte>>& cards) {
	PlayerCardsMessage message(client, nlohmann::json());

	message.cards = &cards;

	client.send_message(message);
}

void PlayerCardsMessage::deserialized() {
}

nlohmann::json PlayerCardsMessage::serialized() {
	nlohmann::json json;
	nlohmann::json jsonArray;

	for (auto it = cards->begin(); it != cards->end(); it++) {
		nlohmann::json jsonCard;
		Carte& card = **it;

		jsonCard["value"] = card.getValue();
		jsonCard["penaltyPoint"] = card.getPenaltyPoint();
		jsonArray.push_back(jsonCard);
	}
	json["cards"] = jsonArray;
	return json;
}