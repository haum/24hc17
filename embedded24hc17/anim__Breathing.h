#include "AnimManager.h"

namespace anim {
namespace Breathing {
	struct Data {
		int divider;
		int step;
		bool up;
	};
	void init_data(void * data);
	void play(void * data);
}
}
