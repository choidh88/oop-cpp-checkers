#include "Pos.h"
#include <cctype>

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

Pos Pos::interpret_coordinates(std::string coordinates)
{
    // coordinates' length must be 2.
    // (col)(row) style
    // (1) alphabet + number
    // (2) alphabet + alphabet

    if (coordinates.length() != 2)
        return Pos(-1, -1);

    char col = toupper(coordinates[0]), row = toupper(coordinates[1]);
    int col_coordinate = col - 'A';
    int row_coordinate = -1;
    if ('0' <= row && row <= '9')
        row_coordinate = row - '0';
    else if ('A' <= row && row <= 'F')
        row_coordinate = row - 'A';

    return Pos(row_coordinate, col_coordinate);
}
