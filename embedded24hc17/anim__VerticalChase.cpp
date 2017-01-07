#include "anim__VerticalChase.h"

namespace anim {

	namespace VerticalChase {

		const constexpr int Ring1[7] = {0, 1, 2, 9, 3, 4, 5};
		const constexpr int Ring2[7] = {6, 7, 8, 9, 10, 11, 12};

		void init_data(void* p, int ring, int wait, CRGB color)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->wait = wait;
			d->step = 0;
			switch(ring)
			{
				case 0:
					d->ring = Ring1;
					break;
				case 1:
					d->ring = Ring2;
					break;
			}
			d->dir = 0;
			d->color = color.b | (color.g << 8) | (color.r << 16);
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);
			if (d->divider == d->wait)
			{
				d->divider = 0;
				AnimManager::setLed(d->ring[d->step], CRGB::Black);
				if (d->dir == 0)
				{
					if (d->step < 6)
					{

						d->step++;
					}
					else
					{
						d->step = 6;
						d->dir = 1;
					}
				}
				else
				{
					if (d->step > 0)
					{

						d->step--;
					}
					else
					{
						d->step = 0;
						d->dir = 0;
					}					
				}
				AnimManager::setLed(d->ring[d->step], d->color);
			}
			else
			{
				d->divider++;
			}
		}

	}

}
