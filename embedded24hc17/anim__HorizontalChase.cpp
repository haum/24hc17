#include "anim__HorizontalChase.h"

namespace anim {
	
	namespace HorizontalChase {

		const constexpr int BottomRing[4] = {0, 6, 5, 12};
		const constexpr int MiddleRing[4] = {1, 7, 4, 11};
		const constexpr int TopRing[4] = {2, 8, 3, 10};

		void init_data(void* p, int ring, int dir, int wait, CRGB color)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->wait = wait;
			d->step = 0;
			d->dir = dir;
			switch(ring)
			{
				case 0:
					d->ring = BottomRing;
					break;
				case 1:
					d->ring = MiddleRing;
					break;
				case 2:
					d->ring = TopRing;
					break;
			}
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
					if (d->step < 3)
					{

						d->step++;
					}
					else
					{
						d->step = 0;
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
						d->step = 3;
					}					
				}
				AnimManager::setLed(d->ring[d->step], d->color);
			}
			else
			{
				d->divider++;
			}
		}


		void increase_wait(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->wait += 5;
		}

		void decrease_wait(void* p)
		{
			auto d = static_cast<Data*>(p);
			if (d->wait>9)
			{
				d->wait -= 5;
			}
			else
			{
				d->wait = 5;
			}
		}

		void inverse_dir(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->dir = 1 - d->dir;
		}

	}

}
