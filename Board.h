#ifndef __BOARD_H__
#define __BOARD_H__

#include "Pos.h"
#include "Player.h"
#include <vector>

class Piece;

// Class that manages the entire board state and game logic
class Board
{
    int rows, cols;
    std::vector<std::vector<Piece *>> board; // Store the board state as a 2D array of piece pointers

public:
    Player players[2]; // Store the two players' information

    Board(int rows = 8, int cols = 8);
    ~Board();

    std::vector<std::vector<Piece *>> get_board() const;
    // Check whether the given Pos is within the valid range of the board
    bool is_in_range(Pos p) const;
    // Return the piece pointer at the given Pos
    Piece *get(Pos p) const;
    // Set the piece pointer at the given Pos
    void set(Pos p, Piece *piece);
    // Check whether the given Pos has no piece
    bool is_empty(Pos p) const;
    // Move a piece from `from` to `to` (including capturing and king promotion)
    int move(Pos from, Pos to);
    // Print the board and each player's current status
    void print_board() const;
    // Check the game-over condition and return the winner's number
    // Return -1 if the game hasn't ended yet
    int game_over() const;
};

#endif
