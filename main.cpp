#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Pos.h"
#include <conio.h>
#include <limits>

using namespace std;

Board before; // Store the board state from the previous turn for undo

// Clear the console screen
void clear();

int main()
{
    int rows, cols;

    clear();

    cout << "[ WELCOME TO CHECKERS FOR WINDOWS ]" << endl;

    // Get the board size and create a Board instance
    cout << "INPUT BOARD'S ROWS(7-16): ";
    cin >> rows;
    if (!(7 <= rows && rows <= 16))
        rows = 8; // Use default value 8 if input is invalid

    cout << "INPUT BOARD'S COLS(7-16): ";
    cin >> cols;
    if (!(7 <= cols && cols <= 16))
        cols = 8; // Use default value 8 if input is invalid

    Board board(rows, cols);

    // Get the names of the two players
    string name;
    cout << "INPUT PLAYER1'S NAME: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin >> ws, name);
    // Set player 1's name and number
    board.players[0].set_name(name);
    board.players[0].set_number(1);

    cout << "INPUT PLAYER2'S NAME: ";
    getline(cin >> ws, name);
    // Set player 2's name and number
    board.players[1].set_name(name);
    board.players[1].set_number(2);

    // Start the game: repeat turns until the outcome is decided
    int turn = 0;
    bool is_undone_turn = false; // Whether this turn was just restored by undo
    while (board.game_over() == -1)
    {
        clear();

        // Reference the current turn's player
        Player &turn_player = board.players[turn % 2];

        // Print the current board state and player info
        board.print_board();
        cout << "----------" << endl;
        cout << "(" << (turn_player.get_number() == 1 ? "WHITE" : "RED") << ") " << turn_player.get_name() << "'S TURN" << endl;

        // Get the starting coordinates of the piece to move
        // Show the UNDO hint unless it's the first turn or right after an undo
        cout << "FROM" << (!is_undone_turn && turn != 0 ? " (If you want to undo, enter 'UNDO')" : "") << ": ";
        string from_coordinates;
        getline(cin >> ws, from_coordinates);
        if (from_coordinates == "UNDO")
        {
            // Undo is only allowed if this isn't the first turn
            if (turn != 0)
            {
                // Restore the previous turn's state
                board = before;
                turn--;
                is_undone_turn = true;
                continue;
            }
            else
            {
                // Undo is not allowed on the first turn
                cout << "THIS IS FIRST TURN." << endl
                     << "enter a character to continue...";
                getch();
                continue;
            }
        }

        // Convert the input string into a Pos coordinate
        Pos from = Pos::interpret_coordinates(from_coordinates);

        // Check whether the target piece is valid
        // Only allow it if the coordinate is on the board, a piece exists there, and it belongs to the current player
        if (!board.is_in_range(from) || board.is_empty(from) || board.get(from)->get_player_number() != turn_player.get_number())
        {
            cout << "THERE IS NO MY PIECE." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // Get the destination coordinates to move to
        cout << "TO: ";
        string to_coordinates;
        getline(cin >> ws, to_coordinates);
        Pos to = Pos::interpret_coordinates(to_coordinates);

        Piece &from_piece = *board.get(from);

        // Check whether the destination coordinate is on the board
        if (!board.is_in_range(to))
        {
            cout << "THERE IS NO VALID DESTINATION." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // Check whether the move is valid according to the piece's movement rules
        if (!from_piece.can_move(board, from, to))
        {
            cout << "CANNOT MOVE THAT WAY." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // Save the board state before the move, for restoring on undo
        before = board;

        // Move the piece, capture, and handle promotion
        board.move(from, to);

        // Prepare for the next turn
        is_undone_turn = false;
        turn++;
    }
}

void clear()
{
    // Run the screen-clear command for Windows consoles (cmd or PowerShell)
    system("cls");
}
