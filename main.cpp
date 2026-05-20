#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Pos.h"

using namespace std;

int main()
{
    int rows, cols;

    cout << "INPUT BOARD'S ROWS(7-16): ";
    cin >> rows;
    if (!(7 <= rows && rows <= 16))
        rows = 8;

    cout << "INPUT BOARD'S COLS(7-16): ";
    cin >> cols;
    if (!(7 <= cols && cols <= 16))
        cols = 8;

    Board board(rows, cols);

    cin.clear();
    string name;
    cout << "INPUT PLAYER1'S NAME: ";
    cin >> name;
    board.players[0].set_name(name);
    board.players[0].set_number(1);

    cin.clear();
    cout << "INPUT PLAYER2'S NAME: ";
    cin >> name;
    board.players[1].set_name(name);
    board.players[1].set_number(2);

    board.print_board();
}