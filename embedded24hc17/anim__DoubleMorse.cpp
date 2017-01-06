#include "anim__DoubleMorse.h"

namespace anim
{
	
	namespace DoubleMorse
	{

		void init_data(void * p, char *phrase1, char *phrase2, int led1, int led2, CRGB onColor1, CRGB onColor2, CRGB endColor1, CRGB endColor2)
		{
			auto d = static_cast<Data*>(p);
			anim::Morse::init_data(&(d->d1), phrase1, led1, onColor1, endColor1);
			anim::Morse::init_data(&(d->d2), phrase2, led2, onColor2, endColor2);
			AnimManager::clear();
		}

		void play(void* p)
		{
			const constexpr int wait = 10;
			auto d = static_cast<Data*>(p);

			if ((d->d1).divider == wait)
			{
				(d->d1).divider = 0;
				send_sign(&(d->d1));
				send_sign(&(d->d2));
			}
			else
			{
				(d->d1).divider++;
			}
		}

	}

}
