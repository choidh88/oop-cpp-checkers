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
    // Input format: a 2-character string, given as (column)(row)
    // (1) letter + digit
    // (2) letter + letter (when the row is 10 or greater)

    // Treat as an invalid coordinate if the length isn't 2
    if (coordinates.length() != 2)
        return Pos(-1, -1);

    char col = toupper(coordinates[0]), row = toupper(coordinates[1]);
    // Convert the column character into a 0-based index ('A' -> 0, 'B' -> 1, ...)
    int col_coordinate = col - 'A';
    int row_coordinate = -1;
    if ('0' <= row && row <= '9')
        row_coordinate = row - '0'; // Convert digit character -> integer
    else if ('A' <= row && row <= 'F')
        row_coordinate = row - 'A' + 10; // Convert letter character -> integer 10 or above

    return Pos(row_coordinate, col_coordinate);
}
