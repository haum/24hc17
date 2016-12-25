#include "anim__RotBeacon.h"

namespace anim {
namespace RotBeacon {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 150;
		const constexpr int bars[4][3] = {
			{0, 1, 2},
			{6, 7, 8},
			{3, 4, 5},
			{10, 11, 12}
		};
		auto d = static_cast<Data*>(p);
		if (d->divider==wait/10) {
			d->divider = 0;
			for (int ii = 0; ii < 13; ++ii) {
				AnimManager::setLed(ii, CRGB::Black);
			}
			for (int ii = 0; ii < 3; ++ii) {
				AnimManager::setLed(bars[d->step][ii], CRGB::Red);
			}
			d->step = d->step==3 ? 0 : d->step+1;
		} else {
			d->divider++;
		}
	}

}
}
