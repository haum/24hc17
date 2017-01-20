#include <SerialCommunicator.h>
#include <EncodedState.h>
#include <iostream>

int main(int argc, char **argv) {
	int inc = 1;

	if (argc != 2 && argc != 3) {
		std::cerr << "usage: " << argv[0] << " <token> [increment]" << std::endl;
		return 1;
	}
	if (argc == 3)
		inc = atoi(argv[2]);

	SerialCommunicator comm;
	EncodedState state;
	state.fromString(argv[1]);
	state.print(comm);
	state.riddle() = state.riddle() + inc;
	char token[22];
	state.direction() = 0;
	state.toString(token);
	comm.write(token, sizeof(token));
	comm.write("\n", 1);
	return 0;
}
