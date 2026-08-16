#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <vector>

using namespace std;

Board::Board(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    board.resize(rows, vector<Piece *>(cols, nullptr));

    // Place player 1's regular pieces on the top 3 rows (only on odd squares)
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < cols; j++)
            if ((i + j) % 2 == 1)
                board[i][j] = new Man(1);

    // Place player 2's regular pieces on the bottom 3 rows (only on odd squares)
    for (int i = rows - 1; i >= rows - 3; i--)
        for (int j = 0; j < cols; j++)
            if ((i + j) % 2 == 1)
                board[i][j] = new Man(2);
}

Board::~Board()
{
    for (auto &row : board)
        for (auto &p : row)
            delete p;
}

std::vector<std::vector<Piece *>> Board::get_board() const
{
    return board;
}

bool Board::is_in_range(Pos p) const
{
    return (0 <= p.get_x() && p.get_x() < rows) && (0 <= p.get_y() && p.get_y() < cols);
}

Piece *Board::get(Pos p) const
{
    return board[p.get_x()][p.get_y()];
}

void Board::set(Pos p, Piece *piece)
{
    board[p.get_x()][p.get_y()] = piece;
}

bool Board::is_empty(Pos p) const
{
    return get(p) == nullptr;
}

int Board::move(Pos from, Pos to)
{
    if (!is_in_range(from) || !is_in_range(to))
    {
        cout << "Out of range\n";
        return -1;
    }

    Piece *p = get(from);
    if (!p)
    {
        cout << "No piece at source\n";
        return -1;
    }

    if (!p->can_move(*this, from, to))
    {
        cout << "Invalid move\n";
        return -1;
    }

    // Move the piece to the destination
    set(to, p);
    set(from, nullptr);

    int player = p->get_player_number();
    int dr = to.get_x() - from.get_x(); // Row delta (to - from)
    int dc = to.get_y() - from.get_y(); // Column delta (to - from)
    int steps = dr > 0 ? dr : -dr;      // Number of squares moved |dr|

    // If it's a jump move, remove the opponent's piece along the path
    if (steps > 1)
    {
        // Unit vector for moving one square at a time in the movement direction (+1 or -1)
        int row_step = dr > 0 ? 1 : -1;
        int col_step = dc > 0 ? 1 : -1;
        // Walk between from and to, removing the first opponent piece found
        for (int s = 1; s < steps; s++)
        {
            Pos mid(from.get_x() + s * row_step, from.get_y() + s * col_step);
            Piece *mid_piece = get(mid);
            if (mid_piece && mid_piece->get_player_number() != player)
            {
                delete mid_piece;
                set(mid, nullptr);
                players[player - 1].add_win();
                break;
            }
        }
    }

    // Promote a regular piece to a king if it reaches the opponent's back row
    if (!p->is_king_piece())
    {
        int player = p->get_player_number();
        bool promoted = (player == 1 && to.get_x() == rows - 1) ||
                        (player == 2 && to.get_x() == 0);
        if (promoted)
        {
            set(to, new King(player));
            delete p;
        }
    }

    return 1;
}

void Board::print_board() const
{
    Player player1 = players[0], player2 = players[1];

    // Print the match title
    cout << endl;
    cout << player1.get_name() << " VS " << player2.get_name() << endl;
    cout << endl;

    // Print player 1's status
    cout << "[ WHITE: " << player1.get_name() << ", WON PIECES : " << player1.get_won_pieces() << " ]" << endl;
    cout << endl;

    // Print the top border of the board
    cout << "   +";
    for (int j = 0; j < cols; j++)
        cout << "---+";
    cout << endl;

    for (int i = 0; i < rows; ++i)
    {
        // Print the row coordinate (digits for 0-9, letters for 10 and above)
        cout << " " << (i >= 10 ? (char)(i - 10 + 'A') : (char)(i + '0')) << " |";
        for (int j = 0; j < cols; j++)
        {
            // Print the piece's symbol if present, otherwise print a blank square
            if (board[i][j] == nullptr)
                cout << " " << ' ' << " |";
            else
                cout << " " << board[i][j]->get_symbol() << " |";
        }

        cout << endl;
        cout << "   +";
        for (int j = 0; j < cols; j++)
            cout << "---+";
        cout << endl;
    }
    cout << "     ";

    // Print the column coordinates (letters starting from A)
    for (int i = 0; i < cols; i++)
        cout << (char)(i + 'A') << "   ";

    // Print player 2's status
    cout << endl
         << endl;
    cout << "[ RED: " << player2.get_name() << ", WON PIECES : " << player2.get_won_pieces() << " ]" << endl;
    cout << endl;
}

int Board::game_over() const
{
    if (players[0].get_won_pieces() >= 8)
        return players[0].get_number();
    else if (players[1].get_won_pieces() >= 8)
        return players[1].get_number();

    return -1;
}
