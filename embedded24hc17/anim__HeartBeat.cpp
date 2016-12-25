#include "anim__HeartBeat.h"

namespace anim {
namespace HeartBeat {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 110;
		auto d = static_cast<Data*>(p);
		CRGB color;
		if (d->divider == wait/10) {
			d->divider=0;
			switch (d->step) {
				case 1:
					color = CRGB(100, 0, 0);
					break;
				case 0:
				case 2:
					color = CRGB(200, 0, 0);
					break;
				default:
					color = CRGB((int)(255*(1-(d->step-3)/12.0)), 0, 0);
			}
			for (int ii = 0; ii < 13; ++ii) {
				AnimManager::setLed(ii, color);
			}
			d->step = d->step==15 ? 0 : d->step+1;
		} else {
			d->divider++;
		}
	}

}
}
