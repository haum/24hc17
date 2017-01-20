#include "AnimManager.h"

#ifndef ANIM__GRAY_H
#define ANIM__GRAY_H

namespace anim
{

	namespace Gray
	{
		struct Data
		{
			int divider;
			int  step;
			bool numbers[16];
			int wait;
			int onColor;
			int offColor;
			int noColor;
		};

		void init_data(void* p, int missingNumbers[16], int size, int wait = 50, CRGB onColor = CRGB::Lime, CRGB offColor = CRGB::DarkGreen, CRGB noColor = CRGB::White);

		void play(void* p);

		void play_one_number(void* p, int number);

		int get_Gray_index(int number);

	}

}

#endif