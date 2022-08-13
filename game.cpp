#include <iostream>
#include "math.h"
#include <vector>
//#include <cstdlib>

#define BASE_TILE_VALUE 2

class Tile {
public:
    Tile(int value) {
        if (value % BASE_TILE_VALUE == 0) {
            _tile_value = value;
        } else {
            std::cout << "Invalid Number.";
            _tile_value = BASE_TILE_VALUE;
        }
    }
    int GetTile() const {
        return _tile_value;
    }
private:
    int _tile_value;
};

class Board {
public:
    Board(int size) {
        if (size > 10 || size < 2) {
            size = 4;
        }
        _size = size;
        _tile_board = new Tile**[_size];
        for(int i = 0; i < _size; ++i){
            _tile_board[i] = new Tile*[_size];

            for(int j = 0; j < _size; ++j){
                _tile_board[i][j] = nullptr;
            }
        }
    }
    ~Board() {
        for (int i = 0; i < _size; i++) {
            delete [] _tile_board[i];
        }
    }
    // function to slide and merge tiles
    bool TilesMatch(const Tile& left, const Tile& right) {
        return (left.GetTile() == right.GetTile());
    }
    Tile MergeTiles(const Tile& one, const Tile& two) {
        if (!TilesMatch(one, two)) {
            return Tile(BASE_TILE_VALUE);
        }
        return Tile(one.GetTile()*BASE_TILE_VALUE);
    }
    void AddTile() {
        int x, y;
        do {
            x = std::rand()%_size;
            y = std::rand()%_size;
        } while (_tile_board[x][y] != nullptr);
        _tile_board[x][y] = new Tile(BASE_TILE_VALUE);
    }
    void PrintGame() {
        std::cout << std::endl;
        for (int i = 0; i < _size; i++) {
            std::cout<<"|";
            for (int j = 0; j < _size; j++) {
                if (_tile_board[i][j] == nullptr) {
                    std::cout << "   |";
                } else {
                    std::cout << " " << _tile_board[i][j]->GetTile() << " |";
                }
            }
            std::cout<<std::endl;
        }
    }
    bool CheckLoss() {
        bool null_pointers = false;
        for (int i = 0; i < _size; i++) {
           for (int j = 0; j <_size; j++) {
               if (_tile_board[i][j] == nullptr) {
                   null_pointers = true;
               }
           }
        }
        bool matches = false;
        for (int i = 0; i < _size-1; i++) {
           for (int j = 0; j <_size-1; j++) {
               if (_tile_board[i][j] != nullptr&&_tile_board[i+1][j+1] != nullptr&&TilesMatch(*_tile_board[i][j],*_tile_board[i+1][j+1])) {
                   matches = true;
               }
           }
        }
        return matches && null_pointers;
    }
    void SlideDown() {
        std::vector<Tile*> column;
        for (int i = 0; i < _size; i++) {
            //grab tiles in vector
            for (int j = 0; j < _size; j++) {
                if (_tile_board[j][i] != nullptr) {
                    column.push_back(_tile_board[j][i]);
                    _tile_board[j][i] = nullptr;
                }
            }
            //find matches, merge
            for (int j = column.size() - 1; j > 0; j--) {
                if (TilesMatch(*column.at(j), *column.at(j-1))) {
                    *column.at(j-1) = MergeTiles(*column.at(j-1), *column.at(j));
                    column.erase(column.begin()+j);
                }
            }
            //replace in board
            int offset = _size - column.size();
            for (int j = 0; j < column.size(); j++) {
                _tile_board[j+offset][i] = column.at(j);
            }
            column.clear();
        }
    }
    void SlideUp() {
        std::vector<Tile*> column;
        for (int i = 0; i < _size; i++) {
            //grab tiles in vector
            for (int j = 0; j < _size; j++) {
                if (_tile_board[j][i] != nullptr) {
                    column.push_back(_tile_board[j][i]);
                    _tile_board[j][i] = nullptr;
                }
            }
            //find matches, merge
            for (int j = 1; j <column.size(); j++) {
                if (TilesMatch(*column.at(j), *column.at(j-1))) {
                    *column.at(j-1) = MergeTiles(*column.at(j-1), *column.at(j));
                    column.erase(column.begin()+j);
                }
            }
            //replace in board
            for (int j = 0; j < column.size(); j++) {
                _tile_board[j][i] = column.at(j);
            }
            column.clear();
        }
    }
    void SlideLeft() {
        std::vector<Tile*> column;
        for (int i = 0; i < _size; i++) {
            //grab tiles in vector
            for (int j = 0; j < _size; j++) {
                if (_tile_board[i][j] != nullptr) {
                    column.push_back(_tile_board[i][j]);
                    _tile_board[i][j] = nullptr;
                }
            }
            //find matches, merge
            for (int j = 1; j <column.size(); j++) {
                if (TilesMatch(*column.at(j), *column.at(j-1))) {
                    *column.at(j-1) = MergeTiles(*column.at(j-1), *column.at(j));
                    column.erase(column.begin()+j);
                }
            }
            //replace in board
            for (int j = 0; j < column.size(); j++) {
                _tile_board[i][j] = column.at(j);
            }
            column.clear();
        }
    }
    void SlideRight() {
        std::vector<Tile*> column;
        for (int i = 0; i < _size; i++) {
            //grab tiles in vector
            for (int j = 0; j < _size; j++) {
                if (_tile_board[i][j] != nullptr) {
                    column.push_back(_tile_board[i][j]);
                    _tile_board[i][j] = nullptr;
                }
            }
            //find matches, merge
            for (int j = column.size()-1; j > 0; j--) {
                if (TilesMatch(*column.at(j), *column.at(j-1))) {
                    *column.at(j-1) = MergeTiles(*column.at(j-1), *column.at(j));
                    column.erase(column.begin()+j);
                }
            }
            //replace in board
            int offset = _size - column.size();
            for (int j = 0; j < column.size(); j++) {
                _tile_board[i][j+offset] = column.at(j);
            }
            column.clear();
        }
    }


private:
    int _size;
    Tile*** _tile_board;
};


int main() {
    char input;
    Board b = Board(4);
    do {
        std::cin >> input;
        if (input == 'w') { b.SlideUp(); }
        if (input == 's') { b.SlideDown(); }
        if (input == 'a') { b.SlideLeft(); }
        if (input == 'd') { b.SlideRight(); }

        b.AddTile();
        b.PrintGame();
    } while (input != 'f');
}
