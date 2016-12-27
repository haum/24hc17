#include "anim__Morse.h"

namespace anim
{
	
	namespace Morse
	{

		void init_data(void* p, char* phrase = "SOS")
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->phrase = phrase;
			d->tick = 0;
			d->pos = 0;
			d->current_morse = get_morse_char(phrase[0]);
			AnimManager::clear();
		}

		void play(void* p)
		{
			const constexpr int wait = 20;
			auto d = static_cast<Data*>(p);

			if (d->divider == wait)
			{
				d->divider = 0;
				AnimManager::setLed(9, get_morse_sign(d->current_morse, d->tick) ? CRGB::Red : CRGB::Black);
				if (is_last_sign(d->current_morse, d->tick))
				{
					d->pos++;
					d->tick = 0;
					char a = d->phrase(d->pos);
					if (a == '\0')
					{
						d->pos = -1;
					}
					d->current_morse = get_morse_char(a);
				}
				else
				{
					d->tick++;
				}
			}
			else
			{
				d->divider++;
			}
		}



		Morse_char get_morse_char(char letter)
		{
			Morse_char new_morse;
			switch(letter)
			{
/*				case 'a':
				case 'A':

				case 'b':
				case 'B':

				case 'c':
				case 'C':

				case 'd':
				case 'D':
*/				
				case 'o':
				case 'O':
					new_morse.value = 0b00000000000000000000011101110111;
					new_morse.size = 14;
					break;
				case 's':
				case 'S':
					new_morse.value = 0b00000000000000000000000000010101;
					new_morse.size = 8;
					break;
				case ' ':
					new_morse.value = 0b00000000000000000000000000000000;
					new_morse.size = 4;
					break;
				case '\0':
					new_morse.value = 0b00000000000000000000000000000000;
					new_morse.size = 7;
					break;
				default:
					new_morse.value = 0b00000000000000000000000000000000;
					new_morse.size = 4;
			}
			return new_morse;

		}

		bool is_last_sign(Morse_char morse_letter, int pos)
		{
			return (morse_letter.size - 1 == pos);
		}

		bool get_morse_sign(Morse_char morse_letter, int pos)
		{
			return (morse_letter.value & 1<<pos);
		}











	}

}
