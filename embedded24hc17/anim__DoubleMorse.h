#include "AnimManager.h"
#include "anim__Morse.h"

namespace anim
{

	namespace DoubleMorse
	{

		struct Data
		{
			anim::Morse::Data d1;
			anim::Morse::Data d2;
		};

		void init_data(void * p, char *phrase1, char *phrase2, int led1, int led2, CRGB onColor1 = CRGB::Red, CRGB onColor2 = CRGB::Red, CRGB endColor1 = CRGB::Yellow, CRGB endColor2 = CRGB::Yellow);
	
		void play(void * data);

	}

}
