#include "anim__Morse.h"

namespace anim
{
	
	namespace Morse
	{

		void init_data(void* p, char* phrase, int led, int wait, CRGB onColor, CRGB endColor)
		{
			auto d = static_cast<Data*>(p);
			d->divider = 0;
			d->wait = wait;
			strncpy(d->phrase, phrase, 127);
			d->tick = 0;
			d->pos = 0;
			d->current_morse = get_morse_char(phrase[0]);
			d->led = led;
			d->onColor = onColor.b | (onColor.g << 8) | (onColor.r << 16);
			d->endColor = endColor.b | (endColor.g << 8) | (endColor.r << 16);
			AnimManager::clear();
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);

			if (d->divider == d->wait)
			{
				d->divider = 0;
				send_sign(d);
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

		void send_sign(Data* d)
		{
			//Serial.println("Youpi");
			if(d->pos>=0)
			{
				//Serial.println("Youpo");
				AnimManager::setLed(d->led, get_morse_sign(d->current_morse, d->tick) ? d->onColor : CRGB::Black);
			}
			else
			{
				//Serial.println("Youpa");
				AnimManager::setLed(d->led, get_morse_sign(d->current_morse, d->tick) ? d->endColor : CRGB::Black);	
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


		void send_sign(char* phrase, int* char_pos, int* sign_pos, Morse_char* current_morse, int led, CRGB onColor, CRGB endColor)
		{
			if(*char_pos>=0)
			{
				AnimManager::setLed(led, get_morse_sign(*current_morse, *sign_pos) ? onColor : CRGB::Black);
			}
			else
			{
				AnimManager::setLed(led, get_morse_sign(*current_morse, *sign_pos) ? endColor : CRGB::Black);	
			}
			if (is_last_sign(*current_morse, *sign_pos))
			{
				*char_pos++;
				*sign_pos = 0;
				char a = *(phrase + *char_pos);
				if (a == '\0')
				{
					*char_pos = -1;
				}
				*current_morse = get_morse_char(a);
			}
			else
			{
				*sign_pos++;
			}
		}

	}

}
