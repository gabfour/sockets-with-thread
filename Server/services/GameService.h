#ifndef GAMESERVICE_H_
#define GAMESERVICE_H_

#include <memory>
#include <list>
#include <string>

class GameService {
public:
	static GameService& get_instance();

	void init();
private:
	const std::string TAG = "[GameService] ";
	static std::unique_ptr<GameService> instance;
};

#endif