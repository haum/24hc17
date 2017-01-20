#include "GameManager.h"

namespace game {
namespace WhiteRabbit {
	struct Data { int min; char name[200]; };
	void init_data(void * data, int min, const char * const name);
	bool play(void * data, GameManager::GameInfo & info);
}
}
