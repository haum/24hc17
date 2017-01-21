#include "game__Nothing.h"
#include "EncodedState.h"
#include "AnimManager.h"
#include <Arduino.h>

namespace game {
namespace Trap {
	void init_data(void*) {}
	bool play(void*, GameManager::GameInfo & info) {
		AnimManager::animate();
		return false;
	}
}
}
