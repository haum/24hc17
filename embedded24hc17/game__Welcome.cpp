#include "game__Welcome.h"
#include "EncodedState.h"

namespace game {
namespace Welcome {
	void init_data(void*) {}
	bool play(void*, GameManager::GameInfo & info) {
		info.comm.dump_file("/Welcome/message");

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
