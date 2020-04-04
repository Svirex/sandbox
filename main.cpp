#include <cstdlib>

#include "core/Game.h"
#include "core/system/ObjectManager.h"


int main() {
  Game game;
  bool success = game.initialize();
  if (success) {
    game.runLoop();
  }
  game.shutdown();
  OBJECT_MANAGER_STAT;
  return EXIT_SUCCESS;
}
