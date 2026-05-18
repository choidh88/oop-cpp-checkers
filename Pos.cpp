#include "Pos.h"

Pos::Pos(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Pos::get_x() const
{
    return x;
}

int Pos::get_y() const
{
    return y;
}
