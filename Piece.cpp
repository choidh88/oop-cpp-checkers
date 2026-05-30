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

    // 대각선 이동이 아니거나 제자리인 경우 이동 불가하기
    if (adr != adc || adr == 0)
        return false;

    // 1칸 이동: 목적지가 빈 칸인 경우만 허용하기
    if (adr == 1)
        return board.is_empty(to);

    // 2칸 점프: 목적지가 비어 있고, 중간 칸에 말이 있는 경우만 허용하기
    if (adr == 2)
    {
        if (!board.is_empty(to))
            return false;

        // 중간 칸 좌표 계산하기
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

    // 이동 방향 계산하기
    int dr = l - j; // 행 이동량 (to - from)
    int dc = m - k; // 열 이동량 (to - from)

    // 대각선 이동인지 확인하기 (|dr| == |dc|, dr != 0)
    if (dr == 0 || dr * dr != dc * dc)
        return false;

    // 목적지가 빈 칸인지 확인하기
    if (!board.is_empty(to))
        return false;

    // 이동 방향으로 한 칸씩 이동하는 단위 벡터 (+1 또는 -1)
    int row_step = dr > 0 ? 1 : -1;
    int col_step = dc > 0 ? 1 : -1;
    int steps = dr * row_step; // 이동 칸 수 |dr|

    // 경로 순회하기: 킹은 상대 말을 최대 1개만 넘을 수 있고, 아군 말은 이동 불가하기
    int opponent_count = 0;
    for (int step = 1; step < steps; step++)
    {
        Pos current_pos(j + step * row_step, k + step * col_step);
        if (!board.is_empty(current_pos))
        {
            char symbol = board.get(current_pos)->get_symbol();
            // 현재 칸에 있는 말이 상대 말인지 확인하기
            bool is_opponent = (player_number == 1) ? (symbol == 'r' || symbol == 'R')
                                                    : (symbol == 'w' || symbol == 'W');
            if (!is_opponent)
                return false; // 아군 말이 경로에 있으면 이동 불가하기
            if (++opponent_count > 1)
                return false; // 상대 말이 2개 이상이면 이동 불가하기
        }
    }

    return true;
}
