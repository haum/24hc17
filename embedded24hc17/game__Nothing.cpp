#include "game__Nothing.h"
#include "EncodedState.h"

namespace game {
namespace Nothing {
	void init_data(void*) {}
	bool play(void*, GameManager::GameInfo & info) {
		EncodedState newstate;
		char token[22];
		newstate.toString(token);
		info.comm.write(token, sizeof(token));
		info.comm.write("\n", 1);

		return true;
	}
}
}