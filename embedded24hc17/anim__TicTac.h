#include "AnimManager.h"

namespace anim {
namespace TicTac {
  struct Data {
    int divider;
    bool blink;
  };
  void init_data(void * data);
  void play(void * data);
}
}
