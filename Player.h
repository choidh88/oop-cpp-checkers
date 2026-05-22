#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player
{
    std::string name;
    int number;
    int won_pieces;

public:
    // set name and player number and make name uppercase string.
    Player(std::string name = "", int number = 0);
    std::string get_name() const;
    int get_number() const;
    int get_won_pieces() const;
    // set name and make it uppercase string.
    void set_name(std::string n);
    // only 1 or 2.
    void set_number(int n);
    // add one to player's won_pieces variable.
    void add_win();
};

#endif
