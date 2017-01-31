#include "anim__Storm.h"
#include "Arduino.h"


namespace anim
{

	namespace Storm
	{

		void init_data(void* p, int wait, int loopSteps, int maxPause, CRGB backColor)
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
			if (maxPause==0)
			{
				d->maxPause = wait;
			}
			else
			{
				d->maxPause = maxPause + 1;
			}
			d->pause = wait;
			d->onPause = false;
			d->backColor = backColor.b | (backColor.g << 8) | (backColor.r << 16);
			AnimManager::setAllLeds(backColor);
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);
			int led_roll;

			if (d->divider == d->wait and not d->onPause)
			{
				if (d->step == 0)
				{
					AnimManager::setAllLeds(d->backColor);
					for(int i = 0; i<d->loopSteps; i++)
					{
						d->leds[i] = random(0,13);
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
						AnimManager::setAllLeds(d->backColor);
					}

					if (d->step==9)
					{
						d->step = 0;
						d->onPause = true;
						d->pause = random(d->wait, d->maxPause);
						AnimManager::setAllLeds(d->backColor);
					}
					else
					{
						d->step++;
					}	
				}
				d->divider = 0;	
			}
			else if (d->divider == d->pause and d->onPause)
			{
				d->divider = 0;
				d->onPause = false;
			}
			else
			{
				d->divider++;
			}
		}

	}
}
