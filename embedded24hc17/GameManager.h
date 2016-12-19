#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SerialCommunicator.h"
#include "EncodedState.h"

/** Game manager **/
class GameManager {
	public:
		/** Game informations **/
		struct GameInfo {
			SerialCommunicator & comm;
			EncodedState & state;
		};

		/** Set next riddle
		  * @param riddle Riddle number
		  */
		static void set(int riddle);

		/** Play the game
		  * @param info GameInfo object
		  * @param data Game data
		  * @return Should token be asked or not
		  */
		static bool play(GameInfo & info);

	private:
		/** Pointer to current game
		  * @param info GameInfo object
		  * @param data Game data
		  * @return Should token be asked or not
		  */
		static bool (*play_ptr)(void * data, GameInfo & info);
};

#endif // GAMEMANAGER_H
