#include "anim__HuePan.h"

namespace anim {
namespace HuePan {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		d->step = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 100;
		auto d = static_cast<Data*>(p);
		if (d->divider == wait/10) {
			d->divider=0;

			CRGB color = CRGB::Red;
			color.setHue((int)(255*d->step/15.0));

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
