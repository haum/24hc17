#include "anim__ProgressiveVerticalChase.h"

namespace anim {

	namespace ProgressiveVerticalChase {

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
			for(auto & t : d->times)
			{
				t = 0;
			}
			d->dir = 0;
			d->done = false;
			d->dt = 255 / (2 * wait);
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
			
			for(int i; i<7; i++)
			{
				if(d->times[i] < d->dt)
				{
					d->times[i] = 0;
				}
				else 
				{
					d->times[i] += d->dt;
				}
				//Serial.print(d->times[i]);
				//Serial.print("->");
				uint8_t scaler = sin8(d->times[i] - 64);
				AnimManager::setLed(d->ring[i], CRGB(scale8(d->r, scaler), scale8(d->g, scaler), scale8(d->b, scaler)));
				//Serial.print(scaler);
				//Serial.print(" ");
			}
			//Serial.print("\n");
			if (d->divider == d->wait)
			{
				d->divider = 0;
				d->done = false;
				if (d->dir == 0)
				{
					if (d->step < 6)
					{
						d->step++;
					}
					else
					{
						d->step = 5;
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
						d->step = 1;
						d->dir = 0;
					}					
				}

			}
			else
			{
				d->divider++;
			}
		}

	}

}
