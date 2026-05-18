#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player
{
    std::string name;
    int number;
    int won_pieces;

public:
    Player(std::string name = "", int number = 0);
    std::string get_name() const;
    int get_number() const;
    int get_won_pieces() const;
    void set_name(std::string n);
    void set_number(int n);
    void add_win();
};

#endif
