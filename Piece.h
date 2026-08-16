#ifndef __PIECE_H__
#define __PIECE_H__

#include "Pos.h"
#include <iostream>

class Board;

// Abstract base class defining the common properties and interface for all pieces
class Piece
{
protected:
    int player_number; // The number of the player who owns this piece (1 or 2)
    bool is_king;      // Whether this piece is a king

public:
    Piece(int num, bool is_king);
    virtual ~Piece() = default;
    // Return the display character based on the player number and piece type (man/king)
    virtual char get_symbol() const = 0;
    // Return the number of the player who owns this piece
    int get_player_number() const;
    // Check whether this piece is a king
    bool is_king_piece() const;
    // Check whether it's possible to move from `from` to `to`
    virtual bool can_move(Board &board, Pos from, Pos to) const = 0;
};

// Regular piece: a class that can only move one diagonal square or jump two squares
class Man : public Piece
{
public:
    Man(int num);
    // Return the lowercase display character based on the player number
    char get_symbol() const override;
    // Check whether it's possible to move from `from` to `to`
    bool can_move(Board &board, Pos from, Pos to) const override;
};

// King piece: a class that can move diagonally with no distance limit
class King : public Piece
{
public:
    King(int num);
    // Return the uppercase display character based on the player number
    char get_symbol() const override;
    // Check whether it's possible to move from `from` to `to`
    bool can_move(Board &board, Pos from, Pos to) const override;
};

#endif
