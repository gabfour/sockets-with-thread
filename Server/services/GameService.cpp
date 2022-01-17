#include "../utils/Output.h"

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


	Output::GetInstance()->print(TAG, "Game world generated\n");
}