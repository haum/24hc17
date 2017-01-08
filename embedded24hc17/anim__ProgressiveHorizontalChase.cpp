#include "anim__ProgressiveHorizontalChase.h"

namespace anim {
	
	namespace ProgressiveHorizontalChase {

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
			for(auto & t : d->times)
			{
				t = 0;
			}
			d->done = false;
			d->dt = 3 * 255 / (8 * wait);
			if (d->dt == 0)
			{
				d->dt = 1;
			}
			d->r = color.r;
			d->g = color.g;
			d->b = color.b;
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);

			if(not d->done)
			{
				d->times[d->step] = d->dt;
				d->done = true;
			}
			
			for(int i; i<4; i++)
			{
				if(d->times[i] < d->dt)
				{
					d->times[i] = 0;
				}
				else 
				{
					d->times[i] += d->dt;
				}
				uint8_t scaler = sin8(d->times[i] - 64);
				AnimManager::setLed(d->ring[i], CRGB(scale8(d->r, scaler), scale8(d->g, scaler), scale8(d->b, scaler)));
			}

			if (d->divider == d->wait)
			{
				d->divider = 0;
				d->done = false;
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
			d->dt = 255 / (2 * d->wait);
			if (d->dt == 0)
			{
				d->dt = 1;
			}
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
			d->dt = 255 / (2 * d->wait);
			if (d->dt == 0)
			{
				d->dt = 1;
			}
		}

		void inverse_dir(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->dir = 1 - d->dir;
		}

	}

}
