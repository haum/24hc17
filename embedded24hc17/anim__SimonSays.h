#include "AnimManager.h"

namespace anim {

	namespace SimonSays {
	
		struct Data	{
			int divider;
			bool blink;
			int wait;
			int i;
			char sequence[15];
			int led;
			int color;
		};
	
		void init_data(void * data, char * sequence, int wait);
		void play(void * data);
		void get_led(void * data, char color);
	}

}

