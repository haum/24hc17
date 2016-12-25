#include "AnimManager.h"

namespace anim {
namespace RotBeacon {
	struct Data {
		int divider;
		int step;
	};
	void init_data(void * data);
	void play(void * data);
}
}
