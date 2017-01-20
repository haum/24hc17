#include "game__MissingShadesOfGray.h"
#include "EncodedState.h"
#include "Arduino.h"
#include "AnimManager.h"
#include "anim__Gray.h"

namespace game {
namespace MissingShadesOfGray {
	void init_data(void*) {}
	bool play(void*, GameManager::GameInfo & info) {
		info.comm.dump_file("/MissingShadesOfGray/message");
		char ans[4]; 

		int success = 0;
		int faults = 0;

		int n = 3;
		int missingNumbers[16];
		int foundNumbers[16];
		int auxNumbers[16];
		int val;
		bool unic = true;
		for(int i=0; i<n; i++) {
			do {
				val = random(16);
				unic = true;
				for(int j=0; j<i; j++) {
					unic = unic && (missingNumbers[j] != val);
				}
			} while(not unic);
			missingNumbers[i] = val;
		}
		AnimManager::initMissingGray(missingNumbers, n, 150);

		for(int i = 0; i<n; i++) {
			char buffer[20];
			int n = sprintf(buffer, "Number %d: ", i);
			info.comm.write(buffer, n);
			
			int ans_len = info.comm.read(ans, 4);
			int val = strtol(ans, NULL, 2);

			foundNumbers[i] = anim::Gray::get_Gray_index(val);
			if (foundNumbers[i]==-1) {
				faults++;
			}
		}

		int delta = -1;
		if(faults==0) {
			for(int j=0; j<n; j++) {
				if(foundNumbers[j]==missingNumbers[0]) {
					delta = j;
					break;
				}
			}
			if (delta==-1) {
				faults += n;
			} else {
				for (int i=1; i<n; i++) {
					if(foundNumbers[(i+delta) % n]!=missingNumbers[i]) {
						faults++;
					}
				}
			}
		}
		if (faults==0) {
			success = 1;
		}

		EncodedState newstate = info.state;
		newstate.faults() = faults;
		newstate.finalsuccess() = success;
		newstate.direction() = 1;
		newstate.sentence() = random(32);
		char token[22];
		newstate.toString(token);
		info.comm.write("\nVittelius: ", 12);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);
		return true;
	}
}
}
