#include "anim__HorizontalChase.h"

namespace anim {
	
	namespace HorizontalChase {

		const constexpr int BottomRing[4] = {9, 2, 8, 3};
		const constexpr int MiddleRing[4] = {10, 1, 7, 4};
		const constexpr int TopRing[4] = {0, 6, 5, 12};

		void init_data(void* p, int ring, int wait)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->wait = wait;
			d->step = 0;
			switch(ring)
			{
				case 0:
					*(d->ring) = *BottomRing;
					break;
				case 1:
					*(d->ring) = *MiddleRing;
					break;
				case 2:
					*(d->ring) = *TopRing;
					break;
			}
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);
			if (d->divider == d->wait)
			{
				d->divider = 0;
				AnimManager::setLed(d->ring[d->step], CRGB::Black);
				if (d->step < 3)
				{
					d->step++;
				}
				else
				{
					d->step = 0;
				}
				AnimManager::setLed(d->ring[d->step], CRGB::Red);
			}
			else
			{
				d->divider++;
			}
		}

	}

}
