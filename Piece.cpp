#include "Piece.h"

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

    int j = from.get_x(), k = from.get_y(), l = to.get_x(), m = to.get_y();

    if (j - l == -1 || j - l == 1)
        if (k - m == 1 || k - m == -1)
            return true;

    if (j - l == -2 || j - l == 2)
        if (k - m == -2 || k - m == 2)
            return true;

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
    int dr = l - j, dc = m - k;

    // 대각선 이동인지 확인 (|dr| == |dc|, dr != 0)
    if (dr == 0 || dr * dr != dc * dc)
        return false;

    // 목적지가 비어있어야 함
    if (!board.is_empty(to))
        return false;

    int row_step = dr > 0 ? 1 : -1;
    int col_step = dc > 0 ? 1 : -1;
    int steps = dr * row_step; // |dr|

    // 경로 위 상대 말 1개까지만 허용, 아군 말은 불가
    int opponent_count = 0;
    for (int step = 1; step < steps; step++)
    {
        Pos cur(j + step * row_step, k + step * col_step);
        if (!board.is_empty(cur))
        {
            char sym = board.get(cur)->get_symbol();
            bool is_opponent = (player_number == 1) ? (sym == 'r' || sym == 'R')
                                                    : (sym == 'w' || sym == 'W');
            if (!is_opponent)
                return false;
            if (++opponent_count > 1)
                return false;
        }
    }

    return true;
}
