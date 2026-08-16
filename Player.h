#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

// Class that manages a player's name, number, and captured piece count
class Player
{
    std::string name;  // Player name (stored in uppercase)
    int number;        // Player number (1 or 2)
    int won_pieces;    // Number of opponent pieces captured so far

public:
    // Set the name and player number, converting the name to uppercase
    Player(std::string name = "", int number = 0);
    // Return the player's name
    std::string get_name() const;
    // Return the player's number
    int get_number() const;
    // Return the number of pieces captured
    int get_won_pieces() const;
    // Set the name, converting it to uppercase
    void set_name(std::string n);
    // Set the player number (only 1 or 2 allowed)
    void set_number(int n);
    // Increment the number of pieces captured by 1
    void add_win();
};

#endif
