#ifndef __PIECE_H__
#define __PIECE_H__

#include "Pos.h"
#include "Board.h"
#include <iostream>

class Piece
{
protected:
    int player_number;
    bool is_king;

public:
    Piece(int num, bool is_king);
    virtual char get_symbol() const = 0;
    bool is_king_piece() const;
    virtual bool can_move(Board &board, Pos from, Pos to) const = 0;
};

class Man : public Piece
{
public:
    Man(int num);
    char get_symbol() const override;
    bool can_move(Board &board, Pos from, Pos to) const override;
};

class King : public Piece
{
public:
    King(int num);
    char get_symbol() const override;
    bool can_move(Board &board, Pos from, Pos to) const override;
};

#endif
