#include "Board.h"
#include <iostream>
#include <vector>

using namespace std;

Board::Board()
{
    board.resize(rows, vector<Piece *>(cols, nullptr));
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

void Board::move(Pos from, Pos to)
{
    if (!is_in_range(from) || !is_in_range(to))
    {
        cout << "Out of range\n";
        return;
    }

    Piece *p = get(from);
    if (!p)
    {
        cout << "No piece at source\n";
        return;
    }

    if (!p->can_move(*this, from, to))
    {
        cout << "Invalid move\n";
        return;
    }

    set(to, p);
    set(from, nullptr);
}

void Board::print_board() const
{
    Player player1 = players[0], player2 = players[1];

    cout << endl
         << endl
         << endl;
    cout << " \t\t\t\t\t\t\t\t   " << player1.get_name() << " VS " << player2.get_name() << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t" << player1.get_name() << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t    WON PIECES :" << player1.get_won_pieces() << endl;
    cout << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\t\t";
    cout << "   +";
    for (int j = 0; j < cols; j++)
        cout << "---+";
    cout << endl;

    for (int i = 0; i < rows; ++i)
    {
        cout << "\t\t\t\t\t\t\t";
        cout << " " << i << " |";
        for (int j = 0; j < cols; j++)
        {
            cout << " " << board[i][j]->get_symbol() << " |";
        }

        cout << endl;
        cout << "\t\t\t\t\t\t\t";
        cout << "   +";
        for (int j = 0; j < cols; j++)
            cout << "---+";
        cout << endl;
    }
    cout << "\t\t\t\t\t\t\t";
    cout << "     ";
    for (int i = 0; i < rows; i++)
        cout << i << "   ";
    cout << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\t\t\t\t" << player2.get_name() << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t    WON PIECES :" << player2.get_won_pieces() << endl;
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
