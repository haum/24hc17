#include "game__DearCowTummy.h"
#include <cstdlib>
#include <cstring>
#include "Arduino.h"
#include "EncodedState.h"

namespace game {
namespace DearCowTummy {
	void init_data(void*) { }


	bool play(void*, GameManager::GameInfo & info) {
		int plus = 1000;
		int minus = 0;

		info.comm.dump_file("/DearCowTummy/message");
		char ans[4]; 

		int success = 0;
		int fault = 1;

		for(int dec = 9; dec>=0; dec--) {
			char buffer[20];
			int n = sprintf(buffer, "Hours left: %d. ", dec);
			info.comm.write(buffer, n);
			
			int ans_len = info.comm.read(ans, 4);
			long int val = strtol(ans, NULL, 10);

			if (val > plus || val < minus) {
				info.comm.write("Out of bounds.\n", 15);
			} else {
				if (plus - val ==  val - minus) {
					if (plus - minus == 2) {
						fault = 0;
						success = 1;
						break;
					} else if (dec > 0) {
						if (random(2)) {
							minus = val;
							info.comm.write("Plus.\n", 6);
						} else {
							plus = val;
							info.comm.write("Minus.\n", 7);
						}
					}
				} else if (dec > 0) {
					if (plus - val > val - minus) {
						minus = val;
						info.comm.write("Plus.\n", 6);
					} else {
						plus = val;
						info.comm.write("Minus.\n", 7);
					}
				}
			}
		}

		EncodedState newstate = info.state;
		newstate.faults() = fault;
		newstate.finalsuccess() = success;
		newstate.direction() = 1;
		newstate.sentence() = random(32);
		char token[22];
		newstate.toString(token);
		info.comm.write("\nToken: ", 8);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);
		return true;
	}
}
}
