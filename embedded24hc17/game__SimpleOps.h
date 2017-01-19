#include "GameManager.h"

namespace game {
namespace SimpleOps {
	struct Data { int faults; long start_millis; };
	void init_data(void * data);
	bool play(void * data, GameManager::GameInfo & info);
}
}
