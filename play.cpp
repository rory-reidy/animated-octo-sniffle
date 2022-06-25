#include "game2048.hpp"
#include "colors-master/colors.h"

int main() {
  game2048 game = game2048(4);
  setbgcolor(50,20,200);
  setcolor(255,255,255);
  set_raw_mode(true); //Turns on non-blocking I/O
  while (true) {
    int ch = quick_read();
    if (ch == RIGHT_ARROW || ch == LEFT_ARROW || ch == DOWN_ARROW || ch == UP_ARROW) { //It can read arrow keys, etc., which are impossible to get with cin
      if (ch == RIGHT_ARROW) {
        std::cout << "right";
      } else if (ch == LEFT_ARROW) {
        std::cout << "left";
      } else if (ch == DOWN_ARROW) {
        std::cout << "down";
      } else if (ch == UP_ARROW) {
        std::cout << "up";
      }
      game.printBoard();
      game.newNumber();
    }
  }
}
