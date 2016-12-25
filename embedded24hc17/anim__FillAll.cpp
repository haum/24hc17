#include "anim__FillAll.h"

namespace anim {
namespace FillAll {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 200;
		auto d = static_cast<Data*>(p);
		if (d->divider == wait/10) {
			d->divider = 0;

			AnimManager::setLed(d->step, d->blink ? CRGB::DarkViolet : CRGB::Black);

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
