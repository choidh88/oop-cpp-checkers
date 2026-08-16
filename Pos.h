#ifndef __POS_H__
#define __POS_H__
#include <iostream>

// Class that stores a coordinate (row, column) on the board
class Pos
{
    int x, y; // x: row index, y: column index

public:
    Pos(int x = 0, int y = 0);
    // Return the row index
    int get_x() const;
    // Return the column index
    int get_y() const;

public:
    // Convert a string coordinate into a Pos instance
    static Pos interpret_coordinates(std::string coordinate);
};

#endif
