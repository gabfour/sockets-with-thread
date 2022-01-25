#include "CardService.h"
#include "../GameConfig.h"
#include "../utils/Output.h"

#include <cstdlib>      // std::rand, std::srand
#include <algorithm>
#include <vector>

std::unique_ptr<CardService> CardService::instance;

CardService& CardService::get_instance() {
	if (instance.get() == nullptr) {
		instance = std::unique_ptr<CardService>(new CardService());
	}
	return *instance;
}

void CardService::generate_game_cards() {
	Output::GetInstance()->print_debug(TAG, "Generating game cards...\n");
	for (int i = 1; i <= MAX_CARDS; i++) {
		int dizaine = (int)floor(i / 10);
		int unite = i - dizaine * 10;
		int penaltyPoint = 1;

		if (unite == dizaine) {
			penaltyPoint = 5;
		}
		else if (i % 10 == 0) {
			penaltyPoint = 3;
		}
		else if (i % 5 == 0) {
			penaltyPoint = 2;
		}

		std::unique_ptr<Carte> card(new Carte(i, penaltyPoint));
		gameCards.push_back(std::move(card));
	}
	Output::GetInstance()->print_debug(TAG, gameCards.size(), " Game cards generated\n");
}

void CardService::randomize_game_cards() {
	std::vector<std::unique_ptr<Carte>> temp;
	for (auto it = gameCards.begin(); it != gameCards.end(); it++) {
		temp.push_back(std::move(*it));
	}
	gameCards.clear();

	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(temp.begin(), temp.end(), generator);

	for (auto it = temp.begin(); it != temp.end(); it++) {
		gameCards.push_back(std::move(*it));
	}
}

std::list<std::unique_ptr<Carte>> CardService::draw_cards(int nbr_cards) {
	std::list<std::unique_ptr<Carte>> result;
	for (int i = 0; i < nbr_cards && gameCards.size() > 0; i++) {
		auto card = std::move(gameCards.front());
		gameCards.pop_front();

		result.push_back(std::move(card));
	}
	return result;
}

std::list<std::unique_ptr<Carte>>& CardService::get_game_cards() {
	return gameCards;
}

void CardService::dispay_cards(std::list<std::unique_ptr<Carte>>& cards) {
	for (auto card = cards.begin(); card != cards.end();card++) {
		dispay_card(**card);
	}
}
void CardService::dispay_card(Carte& card) {
	Output::GetInstance()->print_debug(TAG, "Card(value=",card.getValue(), ", penaltyPoint=",card.getPenaltyPoint(), ")\n");
}