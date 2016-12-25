#include "anim__Breathing.h"

namespace anim {
namespace Breathing {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		d->up = true;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 50;
		auto d = static_cast<Data*>(p);
		if (d->divider == wait/10) {
			d->divider=0;

			float scaler = d->up ? d->step/20.0 : (1-d->step/40.0);
			int r = scaler*232;
			int g = scaler*50;
			int b = scaler*0;
			CRGB color = CRGB(r, g, b);

			for (int ii = 0; ii < 13; ++ii) {
				AnimManager::setLed(ii, color);
			}

			if (d->up && d->step==20) {
				d->step = 0;
				d->up = !d->up;
			} else if (!d->up && d->step==40) {
				d->step = 0;
				d->up = !d->up;
			} else {
				d->step++;
			}
		} else {
			d->divider++;
		}
	}

}
}
