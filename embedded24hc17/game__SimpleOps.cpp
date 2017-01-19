#include "game__SimpleOps.h"
#include "AnimManager.h"
#include "EncodedState.h"
#include <Arduino.h>
#include <string.h>

namespace game {
	namespace SimpleOps {
		void init_data(void * data) {
			Data * d = static_cast <Data*> (data);
			d->start_millis = 0;
			d->faults = 0;
		}

		bool play(void * data, GameManager::GameInfo & info) {
			Data * d = static_cast <Data*> (data);
			const constexpr int wait = 700;
			d->start_millis = millis();

			int op1 = random(0, 10);
			int op2 = random(0, 10);
			int result = op1*op2;

			// read from serial and convert
			char message[14];
			sprintf(message, "%2d times %2d ?\n", op1, op2);
			info.comm.write(message, sizeof(message));
			char ans[255];
			int len = 0;
			while (millis()-d->start_millis<wait) {
				if (info.comm.available())
					len = info.comm.read(ans, sizeof(ans));
				else
					continue;
				if (len!=0) {
					int cleaned = String(ans).toInt();

					if (result==cleaned) {
						EncodedState newstate;
						newstate.faults() = d->faults;
						newstate.riddle() = info.state.riddle() + 1;
						char token[22];
						newstate.toString(token);
						info.comm.write("\nToken: ", 8);
						info.comm.write(token, sizeof(token));
						info.comm.write("\n", 1);
						return true;
					} else {
						d->faults++;
						return true;
					}
				}
			}
			info.comm.write("\nToo late!\n", 11);
			d->faults++;
			return true;
		}
	}
}
