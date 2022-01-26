#include "../utils/Output.h"
#include <sstream>
#include <iomanip>

#include "GameService.h"
#include "CardService.h"

std::unique_ptr<GameService> GameService::instance;

GameService& GameService::get_instance() {
	if (instance.get() == nullptr) {
		instance = std::unique_ptr<GameService>(new GameService());
	}
	return *instance;
}

void GameService::init() {
	Output::GetInstance()->print(TAG, "Generating the game world...\n");

	CardService::get_instance().generate_game_cards();
	CardService::get_instance().randomize_game_cards();

	Output::GetInstance()->print_debug(TAG, "All game cards:\n");
	CardService::get_instance().dispay_cards(CardService::get_instance().get_game_cards());

	auto cards = CardService::get_instance().draw_cards(MAX_BOARD_STARTING_LINES);
	create_the_board(cards);
	display_board();

	Output::GetInstance()->print(TAG, "Game world generated\n");
}

static bool compare_card(const std::unique_ptr<Carte>& first, const std::unique_ptr<Carte>& second)
{
	return first->getValue() < second->getValue();
}

void GameService::create_the_board(std::list<std::unique_ptr<Carte>>& cards) {
	cards.sort(compare_card);
	Output::GetInstance()->print_debug(TAG, "Board cards(",cards.size(), ") : \n");
	CardService::get_instance().dispay_cards(cards);

	for (int y = 0; y < MAX_BOARD_STARTING_LINES && cards.size() > 0;y++) {
		std::list<std::unique_ptr<Carte>> row_x;

		row_x.push_back(std::move(cards.front()));
		cards.pop_front();

		board.push_back(std::move(row_x));
	}
}

void GameService::display_board() {
	auto it_y = board.begin();
	for (int y = 0; y < MAX_BOARD_STARTING_LINES && it_y != board.end(); y++) {
		Output::GetInstance()->print_debug(TAG);
		std::list<std::unique_ptr<Carte>>& row = *it_y;
		auto it_x = row.begin();
		for (int x = 0; x < MAX_BOARD_LINE_CARDS; x++) {
			if (it_x != row.end()) {
				Carte& card = **it_x;

				std::stringstream ss;
				ss << std::setw(3) << std::setfill('*') << card.getValue();

				Output::GetInstance()->print_debug(ss.str(), ",", card.getPenaltyPoint(), "|");
				it_x++;
			}
			else {
				Output::GetInstance()->print_debug("***,*|");
			}
		}
		Output::GetInstance()->print_debug("\n");
		it_y++;
	}
}