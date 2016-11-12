#include "GameManager.h"

namespace AveCaesar {
	struct Data { int faults; };
	void init_data(void * data);
	bool play(void * data, GameManager::GameInfo & info);
}
