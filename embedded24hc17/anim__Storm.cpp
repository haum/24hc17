#include "anim__Storm.h"
#include "Arduino.h"


namespace anim
{

	namespace Storm
	{

		void init_data(void* p, int wait, int loopSteps)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->loopSteps = loopSteps;
			for(int i=0; i<13; i++)
			{
				d->leds[i] = 0;
			}
			d->step = 0;
			d->wait = wait;
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);
			int led_roll;

			if (d->divider == d->wait)
			{
				if (d->step == 0)
				{
					AnimManager::clear();
					for(int i = 0; i<d->loopSteps; i++)
					{
						d->leds[i] = random(0,12);
					}
					d->step++;
				}
				else
				{
					if (d->step % 2)
					{
						for(int i = 0; i<d->loopSteps; i++)
						{
							AnimManager::setLed(d->leds[i], CRGB::White);
						}
					}
					else
					{
						AnimManager::clear();
					}

					if (d->step==5)
					{
						d->step = 0;
					}
					else
					{
						d->step++;
					}	
				}
				d->divider = 0;
								
			}
			else
			{
				d->divider++;
			}
		}

	}
}
