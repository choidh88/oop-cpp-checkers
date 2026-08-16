#include "Piece.h"
#include "Board.h"

Piece::Piece(int num, bool is_king)
{
    if (!(num == 1 || num == 2))
        num = -1;
    player_number = num;
    this->is_king = is_king;
}

bool Piece::is_king_piece() const
{
    return is_king;
}

int Piece::get_player_number() const
{
    return player_number;
}

Man::Man(int num) : Piece(num, false)
{
}

char Man::get_symbol() const
{
    switch (player_number)
    {
    case 1:
        return 'w';
    case 2:
        return 'r';
    }
    return ' ';
}

bool Man::can_move(Board &board, Pos from, Pos to) const
{
    if (!board.is_in_range(from) || !board.is_in_range(to))
        return false;

    int dr = to.get_x() - from.get_x();
    int dc = to.get_y() - from.get_y();
    int adr = (dr > 0) ? dr : -dr; // |dr|
    int adc = (dc > 0) ? dc : -dc; // |dc|

    // Not allowed if the move isn't diagonal or stays in place
    if (adr != adc || adr == 0)
        return false;

    // One-square move: only allowed if the destination is empty
    if (adr == 1)
        return board.is_empty(to);

    // Two-square jump: only allowed if the destination is empty and a piece sits in the middle square
    if (adr == 2)
    {
        if (!board.is_empty(to))
            return false;

        // Compute the middle square's coordinates
        Pos mid(from.get_x() + dr / 2, from.get_y() + dc / 2);

        if (board.is_empty(mid))
            return false;

        return true;
    }

    return false;
}

King::King(int num) : Piece(num, true)
{
}

char King::get_symbol() const
{
    switch (player_number)
    {
    case 1:
        return 'W';
    case 2:
        return 'R';
    }
    return ' ';
}

bool King::can_move(Board &board, Pos from, Pos to) const
{
    if (!board.is_in_range(from) || !board.is_in_range(to))
        return false;

    int j = from.get_x(), k = from.get_y();
    int l = to.get_x(), m = to.get_y();

    // Compute the movement direction
    int dr = l - j; // Row delta (to - from)
    int dc = m - k; // Column delta (to - from)

    // Check whether the move is diagonal (|dr| == |dc|, dr != 0)
    if (dr == 0 || dr * dr != dc * dc)
        return false;

    // Check whether the destination is empty
    if (!board.is_empty(to))
        return false;

    // Unit vector for moving one square at a time in the movement direction (+1 or -1)
    int row_step = dr > 0 ? 1 : -1;
    int col_step = dc > 0 ? 1 : -1;
    int steps = dr * row_step; // Number of squares moved |dr|

    // Walk the path: a king may jump over at most one opponent piece, and cannot move through its own pieces
    int opponent_count = 0;
    for (int step = 1; step < steps; step++)
    {
        Pos current_pos(j + step * row_step, k + step * col_step);
        if (!board.is_empty(current_pos))
        {
            char symbol = board.get(current_pos)->get_symbol();
            // Check whether the piece on the current square belongs to the opponent
            bool is_opponent = (player_number == 1) ? (symbol == 'r' || symbol == 'R')
                                                    : (symbol == 'w' || symbol == 'W');
            if (!is_opponent)
                return false; // Cannot move if a friendly piece is on the path
            if (++opponent_count > 1)
                return false; // Cannot move if there are 2 or more opponent pieces
        }
    }

    return true;
}
