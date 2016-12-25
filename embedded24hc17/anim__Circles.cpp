#include "anim__Circles.h"

namespace anim {
namespace Circles {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 1000;
		const constexpr int circles[3][4] = {
			{0, 5, 6, 12},
			{1, 4, 7, 11},
			{2, 3, 8, 10}
		};
		auto d = static_cast<Data*>(p);
		int ii;
		if (d->divider == wait/10) {
			d->divider = 0;
			switch (d->step) {
				case 3:
					AnimManager::setLed(9, CRGB::White);
					break;
				case 4:
					for (ii = 0; ii < 13; ++ii) {
						AnimManager::setLed(ii, CRGB::Black);
					}
					break;
				default:
					for (ii = 0; ii < 4; ++ii) {
						AnimManager::setLed(circles[d->step][ii], CRGB::White);
					}
			}
			d->step = d->step==4 ? 0 : d->step+1;
		} else {
			d->divider++;
		}
	}

}
}
