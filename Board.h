#ifndef __BOARD_H__
#define __BOARD_H__

#include "Piece.h"
#include "Pos.h"
#include "Player.h"
#include <vector>

class Board
{
    int rows, cols;
    std::vector<std::vector<Piece *>> board;

public:
    Player players[2];

    Board();
    ~Board();

    std::vector<std::vector<Piece *>> get_board() const;

    bool is_in_range(Pos p) const;
    Piece *get(Pos p) const;
    void set(Pos p, Piece *piece);
    bool is_empty(Pos p) const;

    void move(Pos from, Pos to);
    void print_board() const;
    int game_over() const;
};

#endif
