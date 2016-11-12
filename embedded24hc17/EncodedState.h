#ifndef ENCODEDSTATE_H
#define ENCODEDSTATE_H

#include "SerialCommunicator.h"

#include <cstdint>

/** Template to get subvalues **/
template <int BITS, int SHIFT>
class EncodedStateValue {
	public:
    /** Constructor
      * @param p Reference to base integer
      */
		EncodedStateValue (uint64_t &p) : p(p) {}

    /** Affectation operator
      * @param rhs Value to copy from
      * @return Reference to current object
      */
		EncodedStateValue & operator= (const int rhs) {
			p &=  ~(((1 << BITS)-1) << SHIFT);
			p |= ((rhs & ((1 << BITS)-1)) << SHIFT);
			return *this;
		}

    /** Integer convertion
      * @return Convertion to integer
      */
		operator int () {
			return (p >> SHIFT) & ((1 << BITS)-1);
		}

	private:
    /** Reference to base integer **/
		uint64_t &p;
};

/** Encoded state representation **/
class EncodedState {
	public:
    /** Id of this board **/
		static int ourid;

    /** Constructor **/
		EncodedState() { id() = ourid; }

    /** Create state from string
      * @param str String to convert
      * @return true if str is valid, false otherwise
      */
		bool fromString(char str[22]);

    /** Convert state to string
      * @param [out] str String representing state
      */
		void toString(char str[22]);

    /** Print decoded state
      * @param comm Communication object
      */
		void print(SerialCommunicator & comm);

    /** Id of the state **/
		EncodedStateValue <16, 0> id() { return {state[0]}; }

    /** Riddle number of the state **/
		EncodedStateValue <8, 16> riddle() { return {state[0]}; }

    /** Fqults number of the state **/
		EncodedStateValue <4, 0> faults() { return {state[1]}; }

	private:
    /** State data **/
		uint64_t state[2] {0, 0};

    /** Magic numbers **/
		static constexpr uint64_t magic1 {1457849334819822135u};
		static constexpr uint64_t magic2 {9401304444795304839u};
};

#endif
