#include "AnimManager.h"

namespace anim {
namespace HuePan {
	struct Data {
		int divider;
		int step;
	};
	void init_data(void * data);
	void play(void * data);
}
}
