#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Pos.h"
#include <limits>

using namespace std;

void clear();

int main()
{
    int rows, cols;

    clear();

    // input board size and make a board instance.
    cout << "INPUT BOARD'S ROWS(7-16): ";
    cin >> rows;
    if (!(7 <= rows && rows <= 16))
        rows = 8;

    cout << "INPUT BOARD'S COLS(7-16): ";
    cin >> cols;
    if (!(7 <= cols && cols <= 16))
        cols = 8;

    Board board(rows, cols);

    // input players' name.
    string name;
    cout << "INPUT PLAYER1'S NAME: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin >> ws, name);
    board.players[0].set_name(name);
    board.players[0].set_number(1);

    cout << "INPUT PLAYER2'S NAME: ";
    getline(cin >> ws, name);
    board.players[1].set_name(name);
    board.players[1].set_number(2);

    int turn = 0;
    while (board.game_over() == -1)
    {
        clear();

        Player &turnPlayer = board.players[turn % 2];

        board.print_board();
        cout << "----------" << endl;
        cout << turnPlayer.get_name() << "'S TURN" << endl;

        cout << "FROM: ";
        string from_coordinates;
        getline(cin >> ws, from_coordinates);
        Pos from = Pos::interpret_coordinates(from_coordinates);

        cout << from.get_x() << ' ' << from.get_y() << endl;

        if (!board.is_in_range(from) || board.is_empty(from))
        {
            cout << "THERE IS NO PIECE." << endl
                 << "enter a character to continue...";
            char a;
            cin >> a;
            continue;
        }

        cout << "TO: ";
        string to_coordinates;
        getline(cin >> ws, to_coordinates);
        Pos to = Pos::interpret_coordinates(to_coordinates);

        cout << to.get_x() << ' ' << to.get_y() << endl;

        Piece &fromPiece = *board.get(from);

        if (!board.is_in_range(to))
        {
            cout << "THERE IS NO PIECE." << endl
                 << "enter a character to continue...";
            char a;
            cin >> a;
            continue;
        }

        if (!fromPiece.can_move(board, from, to))
        {
            cout << "CANNOT MOVE THAT WAY." << endl
                 << "enter a character to continue...";
            char a;
            cin >> a;
            continue;
        }

        board.move(from, to);

        turn++;
    }
}

void clear()
{
    system("cls");
}
