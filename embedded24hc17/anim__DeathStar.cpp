#include "anim__DeathStar.h"
#include "anim__Morse.h"



namespace anim
{

	namespace DeathStar
	{
		
		
		
		void init_data(void * p, char *phrase)
		{
			anim::Morse::init_data(p, phrase, 2, 20, CRGB::Green, CRGB::Red);
		};

		void play(void* p)
		{	
			AnimManager::setMiddleRing(CRGB::WhiteSmoke);
			anim::Morse::play(p);
		}

	}
}
