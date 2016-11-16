#include "GameManager.h"

#include "game__Welcome.h"
#include "game__AveCaesar.h"

namespace {
  union {
    game::Welcome::Data g00;
    game::AveCaesar::Data g01;
  } game_data;
}

bool (*GameManager::play_ptr)(void * data, GameManager::GameInfo & info) = &game::Welcome::play;

void GameManager::set(int riddle) {
  void (*init_data)(void *);
  switch (riddle) {
  case 1:
    init_data = &game::AveCaesar::init_data;
    play_ptr = &game::AveCaesar::play;
    break;
  default:
    init_data = &game::Welcome::init_data;
    play_ptr = &game::Welcome::play;
  }
  init_data(&game_data);
}

bool GameManager::play(GameManager::GameInfo & info) {
  return (*play_ptr)(&game_data, info);
}
