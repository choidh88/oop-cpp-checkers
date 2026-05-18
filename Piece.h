#ifndef __PIECE_H__
#define __PIECE_H__

#include "Pos.h"
#include "Board.h"

class Piece
{
protected:
    int player_number;

public:
    Piece(int num);
    virtual ~Piece();
    int get_player_number() const;
    virtual char get_symbol() const = 0;
    virtual bool is_king_piece() const;
    void show() const;
    virtual bool can_move(Board &board, Pos from, Pos to) = 0;
};

class Man : public Piece
{
public:
    Man(int num);
    char get_symbol() const override;
    bool can_move(Board &board, Pos from, Pos to) override;
};

class King : public Piece
{
public:
    King(int num);
    char get_symbol() const override;
    bool is_king_piece() const override;
    bool can_move(Board &board, Pos from, Pos to) override;
};

#endif
