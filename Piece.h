#ifndef __PIECE_H__
#define __PIECE_H__

#include "Pos.h"
#include <iostream>

class Board;

class Piece
{
protected:
    int player_number;
    bool is_king;

public:
    Piece(int num, bool is_king);
    virtual ~Piece() = default;
    // get a symbol(char) according to its player's number and piece type: man or king.
    virtual char get_symbol() const = 0;
    int get_player_number() const;
    // check if it is king piece.
    bool is_king_piece() const;
    // check if it can move from 'from' coordinates to 'to' coordinates.
    virtual bool can_move(Board &board, Pos from, Pos to) const = 0;
};

class Man : public Piece
{
public:
    Man(int num);
    // get a lowercase symbol(char) according to its player's number.
    char get_symbol() const override;
    // check if it can move from 'from' coordinates to 'to' coordinates.
    bool can_move(Board &board, Pos from, Pos to) const override;
};

class King : public Piece
{
public:
    King(int num);
    // get a uppercase symbol(char) according to its player's number.
    char get_symbol() const override;
    // check if it can move from 'from' coordinates to 'to' coordinates.
    bool can_move(Board &board, Pos from, Pos to) const override;
};

#endif
