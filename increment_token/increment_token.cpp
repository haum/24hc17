#include <SerialCommunicator.h>
#include <EncodedState.h>
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " <token>" << std::endl;
		return 1;
	}

	SerialCommunicator comm;
	EncodedState state;
	state.fromString(argv[1]);
	state.print(comm);
	state.riddle() = state.riddle() + 1;
	char token[22];
	state.toString(token);
	comm.write(token, sizeof(token));
	comm.write("\n", 1);
	return 0;
}
