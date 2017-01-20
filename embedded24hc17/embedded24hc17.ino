#include "SerialCommunicator.h"
#include "EncodedState.h"
#include "GameManager.h"
#include "AnimManager.h"

#include <FS.h>

namespace {
	const constexpr int led = 2;
	SerialCommunicator comm;
	EncodedState state;
	GameManager::GameInfo info {
		comm,
		state,
	};
}

void setup() {
	pinMode(led, OUTPUT);
	digitalWrite(led, HIGH);

	comm.write("24hc17\n", 7);

	EncodedState::ourid = ESP.getChipId();
	state.id() = EncodedState::ourid;

	SPIFFS.begin();

	AnimManager::setup();
      AnimManager::set(51);
}

void loop() {
	if (!GameManager::play(info))
		return;

	comm.write("\nVitellius' answer: ", 20);
	char token[22];
	int len = comm.read(token, sizeof(token));

	EncodedState newstate;
	if (newstate.fromString(token) && newstate.id() == EncodedState::ourid && newstate.direction() == 0) {
		comm.write("\n", 1);
		comm.write(token, len);
		comm.write("\n", 1);
		state = newstate;
		state.print(comm);
		GameManager::set(state.riddle());
		AnimManager::set(state.animation());
	} else {
		comm.write("Unknown token\n", 14);
	}
}
