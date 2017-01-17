#include "game__Nothing.h"
#include "EncodedState.h"

namespace game {
namespace Nothing {
	void init_data(void*) {}
	bool play(void*, GameManager::GameInfo & info) {
		EncodedState newstate = info.state;
		newstate.faults() = 0;
		newstate.finalsuccess() = 1;
		newstate.direction() = 1;
		char token[22];
		newstate.toString(token);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);

		return true;
	}
}
}
