#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

class Player {
    std::string name;
    int number;
    int pieces_won;
public:
    Player(std::string name = "", int number = 0);
    std::string get_name() const;
    int get_number() const;
    int get_pieces_won() const;
    void set_name(std::string n);
    void add_win();
};

#endif
