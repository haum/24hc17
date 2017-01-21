#include "AnimManager.h"

#ifndef ANIM__MORSE__H
#define ANIM__MORSE__H

namespace anim
{

	namespace Morse
	{
		struct Morse_char
		{
			uint32_t value;
			uint8_t size;
		};

		Morse_char get_morse_char(char letter);

		bool is_last_sign(Morse_char morse_letter, int pos);

		bool get_morse_sign(Morse_char morse_letter, int pos);


		struct Data
		{
			int divider;
			int wait;
			int tick;
			char phrase[128];
			int pos;
			int led;
			int onColor;
			int endColor;
			Morse_char current_morse;
		};

		void init_data(void * data, char *phrase, int led = 9, int wait = 15, CRGB onColor = CRGB::Red, CRGB endColor = CRGB::Yellow);
	
		void play(void * data);

		void send_sign(Data* d);

		void send_sign(char* phrase, int* char_pos, int* sign_pos, Morse_char* current_morse, int led, CRGB onColor, CRGB endColor);

	}

}

#endif
