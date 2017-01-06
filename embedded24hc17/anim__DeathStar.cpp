#include "anim__DeathStar.h"
#include "anim__Morse.h"



namespace anim
{

	namespace DeathStar
	{
		
		
		
		void init_data(void* p, char* phrase = "PERDU")
		{
			anim::Morse::init_data(p, phrase);
		};

		void play(void* p)
		{
						
			AnimManager::setMiddleRing(CRGB::WhiteSmoke);
			
			const constexpr int wait = 20;
			auto d = static_cast<Data*>(p);

			if (d->divider == wait)
			{
				d->divider = 0;
				
				if(d->pos>=0)
				{
					AnimManager::setLed(2, get_morse_sign(d->current_morse, d->tick) ? CRGB::Green : CRGB::Black);
				}
				else
				{
					AnimManager::setLed(2, get_morse_sign(d->current_morse, d->tick) ? CRGB::Yellow : CRGB::Black);	
				}
				if (is_last_sign(d->current_morse, d->tick))
				{
					d->pos++;
					d->tick = 0;
					char a = d->phrase[d->pos];
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
				case 'a':
				case 'A':
					new_morse.size =  8;
					new_morse.value = 0b11101;
					break;
				case 'b':
				case 'B':
					new_morse.size = 12;
					new_morse.value = 0b101010111;
					break;
				case 'c':
				case 'C':
					new_morse.size = 14;
					new_morse.value = 0b10111010111;
					break;
				case 'd':
				case 'D':
					new_morse.size = 10;
					new_morse.value = 0b1010111;
					break;
				case 'e':
				case 'E':
					new_morse.size = 4;
					new_morse.value = 0b1;
					break;
				case 'f':
				case 'F':
					new_morse.size = 12;
					new_morse.value = 0b101110101;
					break;
				case 'g':
				case 'G':
					new_morse.size = 12;
					new_morse.value = 0b101110111;
					break;
				case 'h':
				case 'H':
					new_morse.size = 10;
					new_morse.value = 0b1010101;
					break;
				case 'i':
				case 'I':
					new_morse.size = 6;
					new_morse.value = 0b101;
					break;
				case 'j':
				case 'J':
					new_morse.size = 16;
					new_morse.value = 0b1110111011101;
					break;
				case 'k':
				case 'K':
					new_morse.size = 12;
					new_morse.value = 0b111010111;
					break;
				case 'l':
				case 'L':
					new_morse.size = 12;
					new_morse.value = 0b101011101;
					break;
				case 'm':
				case 'M':
					new_morse.size = 10;
					new_morse.value = 0b1110111;
					break;
				case 'n':
				case 'N':
					new_morse.size = 8;
					new_morse.value = 0b10111;
					break;
				case 'o':
				case 'O':
					new_morse.size = 14;
					new_morse.value = 0b11101110111;
					break;
				case 'p':
				case 'P':
					new_morse.size = 14;
					new_morse.value = 0b10111011101;
					break;
				case 'q':
				case 'Q':
					new_morse.size = 16;
					new_morse.value = 0b1110101110111;
					break;
				case 'r':
				case 'R':
					new_morse.size = 10;
					new_morse.value = 0b1011101;
					break;
				case 's':
				case 'S':
					new_morse.size = 8;
					new_morse.value = 0b10101;
					break;
				case 't':
				case 'T':
					new_morse.size = 6;
					new_morse.value = 0b111;
					break;
				case 'u':
				case 'U':
					new_morse.size = 10;
					new_morse.value = 0b1110101;
					break;
				case 'v':
				case 'V':
					new_morse.size = 12;
					new_morse.value = 0b111010101;
					break;
				case 'w':
				case 'W':
					new_morse.size = 12;
					new_morse.value = 0b111011101;
					break;
				case 'x':
				case 'X':
					new_morse.size = 14;
					new_morse.value = 0b11101010111;
					break;
				case 'y':
				case 'Y':
					new_morse.size = 16;
					new_morse.value = 0b1110111010111;
					break;
				case 'z':
				case 'Z':
					new_morse.size = 14;
					new_morse.value = 0b10101110111;
					break;
				case '1':
					new_morse.size = 20;
					new_morse.value = 0b11101110111011101;
					break;
				case '2':
					new_morse.size = 18;
					new_morse.value = 0b111011101110101;
					break;
				case '3':
					new_morse.size = 16;
					new_morse.value = 0b1110111010101;
					break;
				case '4':
					new_morse.size = 14;
					new_morse.value = 0b11101010101;
					break;
				case '5':
					new_morse.size = 12;
					new_morse.value = 0b101010101;
					break;
				case '6':
					new_morse.size = 14;
					new_morse.value = 0b10101010111;
					break;
				case '7':
					new_morse.size = 16;
					new_morse.value = 0b1010101110111;
					break;
				case '8':
					new_morse.size = 18;
					new_morse.value = 0b101011101110111;
					break;
				case '9':
					new_morse.size = 20;
					new_morse.value = 0b10111011101110111;
					break;
				case '0':
					new_morse.size = 22;
					new_morse.value = 0b1110111011101110111;
					break;

				case ' ':
					new_morse.value = 0b00000000000000000000000000000000;
					new_morse.size = 4;
					break;
				case '\0':
					new_morse.value = 0b00000000000000000000000000000001;
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
