#include "EncodedState.h"

uint16_t EncodedState::ourid {0};

void EncodedState::toString(char repr[22]) {
	// Make sure base phases change with any bit
	uint64_t s1 = state[0] ^ state[1];
	uint64_t s2 = state[1] + s1;

	// Modular-inverse magic (not crypto, but good enough and very cheap)
	s1 *= magic1;
	s2 *= magic2;

	// Hand-made base64-like
	auto b64letter = [] (uint32_t nb) -> char {
		if (nb < 26) return nb+'A'; nb -= 26;
		if (nb < 26) return nb+'a'; nb -= 26;
		if (nb < 10) return nb+'0'; nb -= 10;
		if (nb == 0) return '+';
		if (nb == 1) return '/';
		return '=';
	};

	for (int i = 0; i < 11; ++i) {
		uint32_t nb;
		nb = s1 & ((1 << 6) - 1);
		repr[2*i+0] = b64letter(nb);
		s1 >>= 6;
		nb = s2 & ((1 << 6) - 1);
		repr[2*i+1] = b64letter(nb);
		s2 >>= 6;
	}
}

bool EncodedState::fromString(char repr[22]) {
	// Check form
	for (int i = 0; i < 22; ++i) {
		if (!((repr[i] >= 'a' && repr[i] <= 'z') ||
		      (repr[i] >= 'A' && repr[i] <= 'Z') ||
		      (repr[i] >= '0' && repr[i] <= '9') ||
		      repr[i] == '/' || repr[i] == '+'))
			return false;
	}

	// Hand-made un-base64-like
	auto b64nb = [] (char c) -> uint32_t {
		if (c == '+') return 62;
		if (c == '/') return 63; c -= '0';
		if (c < 10) return 52 + c; c -= 'A' - '0';
		if (c < 26) return c; c -= 'a'-'A';
		return c + 26;
	};
	uint64_t s1 = 0, s2 = 0;
	for (int i = 0; i < 10; ++i) {
		s1 |= b64nb(repr[21 - 2*i - 1]);
		s1 <<= 6;
		s2 |= b64nb(repr[21 - 2*i]);
		s2 <<= 6;
	}
	s1 |= b64nb(repr[0]);
	s2 |= b64nb(repr[1]);

	// Modular-inverse magic (not crypto, but good enough and very cheap)
	s1 *= magic2;
	s2 *= magic1;

	// Rebuild states
	state[1] = s2 - s1;
	state[0] = state[1] ^ s1;

	return true;
}

void EncodedState::print(SerialCommunicator & comm) {
	comm.write("{\n\tid=", 6);
	comm.write(id(), SerialCommunicator::FMTHEX);
	comm.write("\n\triddle=", 9);
	comm.write(riddle());
	comm.write("\n\tfaults=", 9);
	comm.write(faults());
	comm.write("\n}\n", 3);
}
