#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <cstdint>

/** Serial communicator
 * Class which manages communication on serial link
 */
class SerialCommunicator {
	public:
		/** Constructor **/
		SerialCommunicator();

		/** Available formats **/
		enum IntFormat { FMTDEC, FMTHEX };

		/** Check for readable data
		  * @return number of readable bytes
		  */
		uint32_t available();

		/** Read data
		  * @param data Buffer
		  * @param max  Size of buffer
		  * @return Length of read data
		  */
		uint32_t read(char * data, uint32_t max);

		/** Write buffer
		  * @param data Buffer
		  * @param len  Length to write
		  */
		void write(char const * const data, uint32_t len);

		/** Write number
		  * @param data Number
		  * @param fmt  Format
		  */
		void write(int data, IntFormat fmt = FMTDEC);

		/** Dump file from SPIFFS
		  * @param path Path of file to dump
		  */
		void dump_file(char * path);
};

#endif
