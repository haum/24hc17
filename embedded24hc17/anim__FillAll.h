#include "AnimManager.h"

namespace anim {
namespace FillAll {
	struct Data {
		int divider;
		int step;
		bool blink;
	};
	void init_data(void * data);
	void play(void * data);
}
}
