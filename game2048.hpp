#ifndef game2048_HPP
#define game2048_HPP

#include "Number.hpp"
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>

class game2048 {
private:
  Number ** board;
  void initBoard(int x, int y) {
    board = new Number*[x];
    for (int i = 0; i < x; i++) {
      Number k[y];
      board[i] = k;
      for (int j = 0; j < y; j++) {
        k[j] = Number(true);
        std::cout<<k[j].getVal()<<" == "<<board[i][j].getVal()<<std::endl;
        system("clear");
      }
      board[i] = k;
    }
  }
  int rows, cols;
public:
  game2048(int x, int y) {
    rows = x;
    cols = y;
    initBoard(x,y);
  }
  game2048(int x) {
    rows=x;
    cols=x;
    initBoard(x,x);
  }
  void printBoard() {
    //system("clear");
    int maxlength = 0;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cout<<board[i][j].getVal();
      }
        std::cout<<std::endl;
    }
  }
  void move(int dir) {
    // 0 == up
    if (dir == 0) {
      moveUp();
    } else if (dir == 1) {
      moveDown();
    } else if (dir == 2) {
      moveLeft();
    } else {
      moveRight();
    }
  }
  void moveUp();
  void moveDown();
  void moveLeft(){};
  void moveRight(){};
  void newNumber() { board[0][0] = new Number(false);}
};


void game2048::moveUp() {
  for (int i = 0; i < cols; i++) {
    // go through a column, collect a vector of numbers
    std::vector<Number> vec = std::vector<Number>();
    for (int j = 0; j < rows; j++) {
      if (board[i][j].isNum()) {
          vec.push_back(board[i][j]);
      }
    }
    // collapse vector;
    for (std::vector<Number>::iterator it = vec.begin(); it < vec.end(); i++) {
      std::vector<Number>::iterator jt = next(it);
      int a = ((*it)).getVal();
      int b = ((*jt)).getVal();
      if (a == b) {
        Number aN = Number(*it);
        aN.doubleVal();
        (*it) = aN;
        vec.erase(jt);
      }
    }
    // move columns up as far as they can go
    for (int j = 0; j < rows; j++) {
      Number nA = Number(vec.at(j));
      board[i][j] = nA;
    }
  }
}

void game2048::moveDown() {
  for (int i = 0; i < cols; i++) {
    // go through a column, collect a vector of numbers
    std::vector<Number> vec = std::vector<Number>();
    for (int j = 0; j < rows; j++) {
      if (board[i][j].isNum()) {
          vec.push_back(board[i][j]);
      }
    }
    std::reverse(vec.begin(), vec.end());
    for (std::vector<Number>::iterator it = vec.begin(); it < vec.end(); i++) {
      std::vector<Number>::iterator jt = next(it);
      int a = ((*it)).getVal();
      int b = ((*jt)).getVal();
      if (a == b) {
        Number aN = Number(*it);
        aN.doubleVal();
        (*it) = aN;
        vec.erase(jt);
      }
    }
    // move columns up as far as they can go
    for (int j = 0; j < rows; j++) {
      board[i][j] = vec.at(j);
    }
  }
}

#endif
