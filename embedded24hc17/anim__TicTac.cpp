#include "anim__TicTac.h"

namespace anim {
namespace TicTac {

	void init_data(void* p) {
		auto d = static_cast<Data*>(p);
		d->divider = 0;
		AnimManager::clear();
	}

	void play(void* p) {
		const constexpr int wait = 200;
		auto d = static_cast<Data*>(p);
		if (d->divider == wait/10) {
			d->divider = 0;
			d->blink = !d->blink;
			AnimManager::setLed(9, d->blink ? CRGB::Red : CRGB::Black);
		} else {
			d->divider++;
		}
	}

}
}
