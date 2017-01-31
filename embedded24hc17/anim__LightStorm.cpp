#include "anim__LightStorm.h"
#include "Arduino.h"


namespace anim
{

	namespace LightStorm
	{

		void init_data(void* p, int wait, int loopSteps)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->loopSteps = loopSteps;
			d->wait = wait;
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);
			int led_roll;

			if (d->divider == d->wait)
			{
				AnimManager::clear();
				d->divider = 0;
				for(int i = 0; i<d->loopSteps; i++)
				{
					AnimManager::setLed(random(0,13), CRGB::White);
				}				
			}
			else
			{
				d->divider++;
			}
		}

	}
}
