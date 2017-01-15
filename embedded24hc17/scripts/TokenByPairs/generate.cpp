#include <functional>
#include <random>
#include <chrono>
#include "../../EncodedState.h"
#include "../../SerialCommunicator.h"

int main() {
	SerialCommunicator s;

	int base = 94; // (3*N-1)/2 avec N=63
	std::vector <EncodedState> falsestates(base);

	std::default_random_engine generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(0, 65535);
	auto alea = std::bind(distribution, generator);

	for (auto & e : falsestates) {
		e.id() = 0;
		e.riddleparams() = alea();
		e.faults() = alea();
		e.animation() = alea();
		e.sentence() = alea();
		e.finalsuccess() = 0;
		e.direction() = 0;
		e.riddle() = alea();
		e.animparams() = alea();
		e.checksum() = 0;
	}

	std::vector <int> printablenb(base, 2);
	printablenb[0] = 3;

	std::uniform_int_distribution<int> distributionB(0, base-1);
	auto diceB = std::bind(distributionB, generator);

	for (int i = 0; i < base*2+1; ++i) {
		int t = diceB();
		if (printablenb[t] == 0) {
			for (int j = 0; j < base; ++j) {
				if (printablenb[j%base] != 0) {
					t = j%base;
				}
			}
		}
		--printablenb[t];

		char token[22];
		falsestates[t].toString(token);
		s.write(token, 22);
		s.write(" ", 1);
		if (!((i + 1) % 3))
			s.write("\n", 1);
	}
	char token[22];
	falsestates[0].toString(token);
	s.write("\n\n", 2);
	s.write(token, 22);
	s.write("\n", 1);

	return 0;
}
