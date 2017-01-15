#include "GameManager.h"

#include "game__Welcome.h"
#include "game__AveCaesar.h"
#include "game__SimpleFromStorage.h"
#include "game__LostInMaze.h"
#include "game__Nothing.h"

namespace {
	union {
		game::Welcome::Data g00;
		game::AveCaesar::Data g01;
		game::SimpleFromStorage::Data g02;
	} game_data;
}

bool (*GameManager::play_ptr)(void * data, GameManager::GameInfo & info) = &game::Welcome::play;

void GameManager::set(int riddle) {
	switch (riddle) {
		case 1:
			game::AveCaesar::init_data(&game_data);
			play_ptr = &game::AveCaesar::play;
			break;
		case 2:
			game::SimpleFromStorage::init_data(&game_data, "BracesMatch");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 3:
			game::SimpleFromStorage::init_data(&game_data, "MrReverse");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 4:
			game::SimpleFromStorage::init_data(&game_data, "TinyOverflow");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 5:
			game::SimpleFromStorage::init_data(&game_data, "RomanProblems");
			play_ptr = &game::SimpleFromStorage::play;
		case 6:
			game::LostInMaze::init_data(&game_data);
			play_ptr = &game::LostInMaze::play;
			break;
		case 7:
			game::SimpleFromStorage::init_data(&game_data, "TokenByPairs");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 8:
			game::Nothing::init_data(&game_data);
			play_ptr = &game::Nothing::play;
			break;
		case 9:
			game::SimpleFromStorage::init_data(&game_data, "ThreeBigs");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 10:
			game::SimpleFromStorage::init_data(&game_data, "ThreeBigsEviler");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		default:
			game::Welcome::init_data(&game_data);
			play_ptr = &game::Welcome::play;
	}
}

bool GameManager::play(GameManager::GameInfo & info) {
	return (*play_ptr)(&game_data, info);
}
