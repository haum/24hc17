#include "game__Welcome.h"
#include "EncodedState.h"

namespace game {
namespace Welcome {
  void init_data(void*) {}
  bool play(void*, GameManager::GameInfo & info) {
    EncodedState newstate;

    char msg[] = "Welcome in the game.\n\n"
    "Please connect to #24hc17laumii @ freenode (IRC network) and authenticate in Nero system with the following message.\n\n"
    "Nero: ";
    info.comm.write(msg, sizeof(msg));

    char token[22];
    newstate.toString(token);
    info.comm.write(token, sizeof(token));
    info.comm.write("\n", 1);

    return true;
  }
}
}
