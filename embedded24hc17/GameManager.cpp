#include "GameManager.h"

#include "game__Welcome.h"
#include "game__AveCaesar.h"
#include "game__SimpleFromStorage.h"
#include "game__LostInMaze.h"
#include "game__Nothing.h"
#include "game__WhiteRabbit.h"
#include "game__SimpleOps.h"
#include "game__DearCowTummy.h"
#include "game__SimonSays.h"
#include "game__MissingShadesOfGray.h"


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
		case 11:
			game::SimpleFromStorage::init_data(&game_data, "DesreverSort");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 12:
			game::SimpleFromStorage::init_data(&game_data, "JustHexa");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 13:
			game::SimpleFromStorage::init_data(&game_data, "JustHexaEvil");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 14:
			game::DearCowTummy::init_data(&game_data);
			play_ptr = &game::DearCowTummy::play;
		case 15:
			game::SimpleFromStorage::init_data(&game_data, "Difference");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 16:
			game::SimpleFromStorage::init_data(&game_data, "DifferenceUnknown");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 17:
			game::WhiteRabbit::init_data(&game_data, 50, "WhiteRabbitEasy");
			play_ptr = &game::WhiteRabbit::play;
			break;
		case 18:
			game::WhiteRabbit::init_data(&game_data, 257, "WhiteRabbitLinear");
			play_ptr = &game::WhiteRabbit::play;
			break;
		case 19:
			game::SimpleOps::init_data(&game_data);
			play_ptr = &game::SimpleOps::play;
			break;
		case 20:
			game::SimpleFromStorage::init_data(&game_data, "TathamFilling");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 21:
			game::SimpleFromStorage::init_data(&game_data, "RotateAscii");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 22:
			game::SimpleFromStorage::init_data(&game_data, "SudXtrem");
			play_ptr = &game::SimpleFromStorage::play;
			break;
		case 23:
			game::SimonSays::init_data(&game_data);
			play_ptr = &game::SimonSays::play;
			break;
		case 24:
			game::MissingShadesOfGray::init_data(&game_data);
			play_ptr = &game::MissingShadesOfGray::play;
			break;
		case 25:
			game::SimpleFromStorage::init_data(&game_data, "DifferenceEviler");
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
