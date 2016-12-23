#include "GameManager.h"

namespace game {
namespace SimpleFromStorage {
	struct Data { char name[200]; };
	void init_data(void * data, const char * const name);
	bool play(void * data, GameManager::GameInfo & info);
}
}
