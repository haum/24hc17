#include "anim__Fiesta.h"
#include "Arduino.h"


namespace anim
{

	namespace Fiesta
	{
		CRGB colors[13] = {
			CRGB::White,
			
			CRGB::Red,
			CRGB::Lime,
			CRGB::Blue,
			
			CRGB::Yellow,
			CRGB::Aqua,
			CRGB::Magenta,
			
			CRGB::Maroon,
			CRGB::Green,
			CRGB::Navy,

			CRGB::Olive,
			CRGB::Teal,
			CRGB::Purple
		};

		void init_data(void* p, int wait = 200, int loopSteps = 1)
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
				d->divider = 0;
				for(int i = 0; i<d->loopSteps; i++)
				{
					bool blink = random(0, 2);
					if (blink)
					{
						AnimManager::setLed(random(0,12), colors[random(0, 12)]);
					}
					else
					{
						AnimManager::setLed(random(0,12), CRGB::Black);
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
