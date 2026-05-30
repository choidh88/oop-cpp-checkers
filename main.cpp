#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Pos.h"
#include <conio.h>
#include <limits>

using namespace std;

Board before; // 무르기를 위해 직전 턴의 보드 상태 저장하기

// 콘솔 화면 지우기
void clear();

int main()
{
    int rows, cols;

    clear();

    cout << "[ WELCOME TO CHECKERS FOR WINDOWS ]" << endl;

    // 보드 크기 입력받아 Board 인스턴스 생성하기
    cout << "INPUT BOARD'S ROWS(7-16): ";
    cin >> rows;
    if (!(7 <= rows && rows <= 16))
        rows = 8; // 유효하지 않은 입력인 경우 기본값 8 사용하기

    cout << "INPUT BOARD'S COLS(7-16): ";
    cin >> cols;
    if (!(7 <= cols && cols <= 16))
        cols = 8; // 유효하지 않은 입력인 경우 기본값 8 사용하기

    Board board(rows, cols);

    // 두 플레이어의 이름 입력받기
    string name;
    cout << "INPUT PLAYER1'S NAME: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin >> ws, name);
    // 플레이어1 이름과 번호 설정하기
    board.players[0].set_name(name);
    board.players[0].set_number(1);

    cout << "INPUT PLAYER2'S NAME: ";
    getline(cin >> ws, name);
    // 플레이어2 이름과 번호 설정하기
    board.players[1].set_name(name);
    board.players[1].set_number(2);

    // 게임 시작: 승패가 결정될 때까지 턴 반복하기
    int turn = 0;
    bool is_undone_turn = false; // 이번 턴이 무르기로 되돌아온 턴인지 여부
    while (board.game_over() == -1)
    {
        clear();

        // 현재 턴의 플레이어 참조하기
        Player &turn_player = board.players[turn % 2];

        // 현재 보드 상태와 플레이어 정보 출력하기
        board.print_board();
        cout << "----------" << endl;
        cout << "(" << (turn_player.get_number() == 1 ? "WHITE" : "RED") << ") " << turn_player.get_name() << "'S TURN" << endl;

        // 이동할 말의 출발 좌표 입력받기
        // 첫 번째 턴이 아니고 이번 턴이 무르기 직후가 아닌 경우 UNDO 안내 표시하기
        cout << "FROM" << (!is_undone_turn && turn != 0 ? " (If you want to undo, enter 'UNDO')" : "") << ": ";
        string from_coordinates;
        getline(cin >> ws, from_coordinates);
        if (from_coordinates == "UNDO")
        {
            // 첫 번째 턴이 아닌 경우 무르기 가능하기
            if (turn != 0)
            {
                // 이전 턴 상태로 복원하기
                board = before;
                turn--;
                is_undone_turn = true;
                continue;
            }
            else
            {
                // 첫 번째 턴에서는 무르기 불가하기
                cout << "THIS IS FIRST TURN." << endl
                     << "enter a character to continue...";
                getch();
                continue;
            }
        }

        // 입력된 문자열을 Pos 좌표로 변환하기
        Pos from = Pos::interpret_coordinates(from_coordinates);

        // 유효한 이동 대상 말인지 확인하기
        // 좌표가 보드 범위 안에 있고, 말이 존재하며, 현재 턴 플레이어의 말인 경우만 허용하기
        if (!board.is_in_range(from) || board.is_empty(from) || board.get(from)->get_player_number() != turn_player.get_number())
        {
            cout << "THERE IS NO MY PIECE." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // 이동할 목적지 좌표 입력받기
        cout << "TO: ";
        string to_coordinates;
        getline(cin >> ws, to_coordinates);
        Pos to = Pos::interpret_coordinates(to_coordinates);

        Piece &from_piece = *board.get(from);

        // 목적지 좌표가 보드 범위 안에 있는지 확인하기
        if (!board.is_in_range(to))
        {
            cout << "THERE IS NO VALID DESTINATION." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // 해당 말의 이동 규칙에 따라 이동 가능한지 확인하기
        if (!from_piece.can_move(board, from, to))
        {
            cout << "CANNOT MOVE THAT WAY." << endl
                 << "enter a character to continue...";
            getch();
            continue;
        }

        // 무르기 요청 시 복원에 사용하기 위해 이동 전 보드 상태 저장하기
        before = board;

        // 말 이동 및 취하기, 승격 처리하기
        board.move(from, to);

        // 다음 턴 준비하기
        is_undone_turn = false;
        turn++;
    }
}

void clear()
{
    // Windows 콘솔(cmd 또는 PowerShell) 전용 화면 지우기 명령 실행하기
    system("cls");
}
