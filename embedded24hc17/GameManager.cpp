#include "GameManager.h"

#include "game__Welcome.h"
#include "game__AveCaesar.h"

namespace {
  union {
    Welcome::Data g00;
    AveCaesar::Data g01;
  } game_data;
}

bool (*GameManager::play_ptr)(void * data, GameManager::GameInfo & info) = &Welcome::play;

void GameManager::set(int riddle) {
  void (*init_data)(void *);
  switch (riddle) {
  case 1:
    init_data = &AveCaesar::init_data;
    play_ptr = &AveCaesar::play;
    break;
  default:
    init_data = &Welcome::init_data;
    play_ptr = &Welcome::play;
  }
  init_data(&game_data);
}

bool GameManager::play(GameManager::GameInfo & info) {
  return (*play_ptr)(&game_data, info);
}
