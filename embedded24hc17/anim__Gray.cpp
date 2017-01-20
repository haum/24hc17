#include "anim__Gray.h"


namespace anim
{

	namespace Gray
	{

		const constexpr int Grays[16] = { 0b0000, 0b0001, 0b0011, 0b0010, 0b0110, 0b0111, 0b0101, 0b0100, 0b1100, 0b1101, 0b1111, 0b1110, 0b1010, 0b1011, 0b1001, 0b1000};
		const constexpr int column[4] = {0, 1, 2, 9};

		void init_data(void* p, int missingNumbers[16], int size, int wait, CRGB onColor, CRGB offColor, CRGB noColor)
		{
			auto d = static_cast<Data*>(p);

			d->divider = 0;
			d->step = 0;
			d->wait = wait;
			for(int i=0; i<16; i++)
			{
				d->numbers[i] = true;
			}			
			for(int i=0; i<size; i++)
			{
				d->numbers[missingNumbers[i]] = false;
			}
			d->onColor = onColor.b | (onColor.g << 8) | (onColor.r << 16);
			d->offColor = offColor.b | (offColor.g << 8) | (offColor.r << 16);
			d->noColor = noColor.b | (noColor.g << 8) | (noColor.r << 16);
		}

		void play(void* p)
		{
			auto d = static_cast<Data*>(p);

			if (d->divider == d->wait)
			{
				d->divider = 0;
				if(d->numbers[d->step])
				{
					play_one_number(p, d->step);
				}
				else
				{
					for(int i=0; i<4; i++)
					{
						AnimManager::setLed(column[i], d->noColor);
					}
				}

				if(d->step < 15)
				{
					d->step++;
				}
				else
				{
					d->step = 0;
				}
			}
			else
			{
				d->divider++;
			}		
		}

		void play_one_number(void* p, int number)
		{
			auto d = static_cast<Data*>(p);

			for(int i=0; i<4; i++)
			{
				 AnimManager::setLed(column[i], (Grays[number] & 1<<i) ? d->onColor : d->offColor);
			}
		}

		int get_Gray_index(int number)
		{
			for(int i=0; i<16; i++) {
				if (Grays[i] == number) {
					return i;
				}
			}
			return -1;
		}

	}

}



