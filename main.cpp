#include <cstdlib>

#include "core/Game.h"


int main() {
  Game game;
  bool success = game.initialize();
  if (success) {
    game.runLoop();
  }
  game.shutdown();
  return EXIT_SUCCESS;
}
