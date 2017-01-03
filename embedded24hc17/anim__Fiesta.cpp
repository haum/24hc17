#include "anim__Fiesta.h"
#include "Arduino.h"


namespace anim
{

	namespace Fiesta
	{
		void init_data(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			AnimManager::clear();
		}

		void play(void* p)
		{
			const constexpr int wait = 200;
			auto d = static_cast<Data*>(p);
			int led_roll;

			if (d->divider == wait/50)
			{
				d->divider = 0;
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
			else
			{
				d->divider++;
			}
		}

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
	}
}
