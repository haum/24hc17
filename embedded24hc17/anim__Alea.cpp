#include "anim__Alea.h"


namespace anim
{

	namespace Alea
	{
		void init_data(void* p)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->led = 9;
			AnimManager::clear();
		}

		void play(void* p)
		{
			const constexpr int wait = 200;
			auto d = static_cast<Data*>(p);
			int led_roll;

			if (d->divider == wait/10)
			{
				d->divider = 0;
				led_roll = distribution(generator);

				AnimManager::setLed(d->led, CRGB::Black);
				d->led = led_roll;
				AnimManager::setLed(d->led, CRGB::Red);
			}
			else
			{
				d->divider++;
			}
		}
	}
}
