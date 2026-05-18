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

    bool in_range(Pos p) const;
    Piece *get(Pos p) const;
    void set(Pos p, Piece *piece);
    bool is_empty(Pos p) const;

    bool move(Player &player, Pos from, Pos to);
    void print_board() const;
    bool game_over() const;
};

#endif
