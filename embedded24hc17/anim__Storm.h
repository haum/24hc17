#include "AnimManager.h"
#include <random>


namespace anim
{

	namespace Storm
	{
	
		struct Data
		{
			int divider;
			int loopSteps;
			int wait;
			int pause;
			int maxPause;
			int step;
			int leds[13];
			bool onPause;
			int backColor;
		};

	 	void init_data(void* p, int wait = 7, int loopSteps = 3, int pause = 0, CRGB backColor = CRGB(0x000011));

		void play(void* p);		
	}

}
