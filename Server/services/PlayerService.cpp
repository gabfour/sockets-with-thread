#include "PlayerService.h"

std::unique_ptr<PlayerService> PlayerService::instance;

PlayerService &PlayerService::get_instance() {
	if (instance == nullptr || instance.get() == nullptr) {
		instance = std::unique_ptr<PlayerService>(new PlayerService());
	}
	return *instance;
}

void PlayerService::add_player(std::unique_ptr<Player> player) {
	if (player == nullptr)return;
	players.push_back(std::move(player));
}

void PlayerService::remove_player(Player&player) {
	players.remove_if([&](const std::unique_ptr<Player>& p1) { return &player == p1.get(); });
}

int PlayerService::get_nbr_players() {
	return players.size();
}