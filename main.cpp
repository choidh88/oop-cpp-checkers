#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Pos.h"
#include <conio.h>
#include <limits>

using namespace std;

Board before;

// clear console window
void clear();

int main()
{
    int rows, cols;

    clear();

    cout << "[ WELCOME TO CHECKERS FOR WINDOWS ]" << endl;

    // input board size and make a board instance.
    cout << "INPUT BOARD'S ROWS(7-16): ";
    cin >> rows;
    if (!(7 <= rows && rows <= 16))
        rows = 8; // default value is 8.

    cout << "INPUT BOARD'S COLS(7-16): ";
    cin >> cols;
    if (!(7 <= cols && cols <= 16))
        cols = 8; // default value is 8.

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

    // game start
    int turn = 0;
    bool is_undone_turn = false;
    while (board.game_over() == -1)
    {
        clear();

        // current turn's player
        Player &turn_player = board.players[turn % 2];

        // print current turn's board and player's status
        board.print_board();
        cout << "----------" << endl;
        cout << "(" << (turn_player.get_number() == 1 ? "WHITE" : "RED") << ") " << turn_player.get_name() << "'S TURN" << endl;

        // inputted from coordinates.
        // or inputted 'UNDO' to undo.
        cout << "FROM" << (!is_undone_turn && turn != 0 ? " (If you want to undo, enter 'UNDO')" : "") << ": ";
        string from_coordinates;
        getline(cin >> ws, from_coordinates);
        if (from_coordinates == "UNDO")
        {
            // if this is not first turn, able to undo.
            if (turn != 0)
            {
                board = before;
                turn--;
                is_undone_turn = true;
                continue;
            }
            else
            {
                // cannot undo if this is first turn.
                cout << "THIS IS FIRST TURN." << endl
                     << "enter a character to continue...";
                getch();
                continue;
            }
        }

        // get Pos coordinates from inputted coordinates string.
        Pos from = Pos::interpret_coordinates(from_coordinates);

        // check if this is valid piece to move.
        if (!board.is_in_range(from) || board.is_empty(from) || board.get(from)->get_player_number() != turn_player.get_number())
        {
            cout << "THERE IS NO MY PIECE." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // inputted to coordinates.
        cout << "TO: ";
        string to_coordinates;
        getline(cin >> ws, to_coordinates);
        Pos to = Pos::interpret_coordinates(to_coordinates);

        Piece &from_piece = *board.get(from);

        // check if this is valid piece (inside the board).
        if (!board.is_in_range(to))
        {
            cout << "THERE IS NO MY PIECE." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // check if this is valid piece to arrive.
        if (!from_piece.can_move(board, from, to))
        {
            cout << "CANNOT MOVE THAT WAY." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // save previous turn's status to undo when user requests.
        before = board;

        // move and win pieces.
        board.move(from, to);

        // preparation steps for next turn.
        is_undone_turn = false;
        turn++;
    }
}

void clear()
{
    // this command is for Windows (cmd or powershell).
    system("cls");
}
