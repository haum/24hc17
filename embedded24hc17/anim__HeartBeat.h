#include "AnimManager.h"

namespace anim {
namespace HeartBeat {
	struct Data {
		int divider;
		int step;
	};
	void init_data(void * data);
	void play(void * data);
}
}
