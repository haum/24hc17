#include "AnimManager.h"

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
			int tick;
			char* phrase;
			int pos;
			Morse_char current_morse;
		};

		void init_data(void * data, char *phrase);
	
		void play(void * data);
	}

}
