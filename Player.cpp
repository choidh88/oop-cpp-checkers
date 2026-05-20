#include "Player.h"
#include <algorithm>

Player::Player(std::string name, int number)
{
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);

    this->name = name;
    this->number = number;
    this->won_pieces = 0;
}

std::string Player::get_name() const
{
    return name;
}

int Player::get_number() const
{
    return number;
}

int Player::get_won_pieces() const
{
    return won_pieces;
}

void Player::set_name(std::string n)
{
    std::transform(n.begin(), n.end(), n.begin(), ::toupper);
    name = n;
}

void Player::set_number(int n)
{
    if (!(n == 1 || n == 2))
        n = -1;
    number = n;
}

void Player::add_win()
{
    won_pieces++;
}
