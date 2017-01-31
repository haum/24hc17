#include "anim__RandomTicking.h"


namespace anim
{

	namespace RandomTicking
	{
		void init_data(void* p, int wait = 20)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
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
				d->blink = !d->blink;
				AnimManager::setLed(9, d->blink ? CRGB::Red : CRGB::Black);
				d->wait = random(1,101);
			}
			else
			{
				d->divider++;
			}
		}
	}
}
