#include "GameManager.h"

namespace game {
namespace Pong {
	struct Data { };
	void init_data(void * data);
	bool play(void * data, GameManager::GameInfo & info);
}
}
