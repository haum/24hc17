#include "GameManager.h"

namespace game {
namespace LostInMaze {
	static constexpr int W {17};
	static constexpr int H {15};

	struct Data {
		char map[H][W];
	};

	void init_data(void * data);
	bool play(void * data, GameManager::GameInfo & info);
}
}
