#include "anim__FillSpiral.h"

namespace anim {
namespace FillSpiral {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 200;
		const constexpr int spiral[13] = {9, 2, 8, 3, 10, 1, 7, 4, 11, 0, 6, 5, 12};

		auto d = static_cast<Data*>(p);
		if (d->divider == wait/10) {
			d->divider = 0;

			AnimManager::setLed(spiral[d->step], d->blink ? CRGB::Blue : CRGB::Black);

			if (d->step==12) {
				d->step = 0;
				d->blink = !d->blink;
			} else {
				d->step++;
			}
		} else {
			d->divider++;
		}
	}

}
}
