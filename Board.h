#ifndef __BOARD_H__
#define __BOARD_H__

#include "Pos.h"
#include "Player.h"
#include <vector>

class Piece;

class Board
{
    int rows, cols;
    std::vector<std::vector<Piece *>> board;

public:
    Player players[2];

    Board(int rows = 8, int cols = 8);
    ~Board();

    std::vector<std::vector<Piece *>> get_board() const;
    // check if given Pos is in valid range of the board.
    bool is_in_range(Pos p) const;
    // get a piece from given Pos.
    Piece *get(Pos p) const;
    // set a piece according to given Pos.
    void set(Pos p, Piece *piece);
    // check if there is not a piece.
    bool is_empty(Pos p) const;
    // move from given 'from' to given 'to'.
    int move(Pos from, Pos to);
    // print the board with player's status.
    void print_board() const;
    // check game over condition and returns winner's number.
    // if the game is not over, it returns -1.
    int game_over() const;
};

#endif
