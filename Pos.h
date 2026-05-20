#ifndef __POS_H__
#define __POS_H__
#include <iostream>

class Pos
{
    int x, y;

public:
    Pos(int x = 0, int y = 0);
    int get_x() const;
    int get_y() const;

public:
    static Pos interpret_coordinates(std::string coordinate);
};

#endif
