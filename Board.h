#ifndef __BOARD_H__
#define __BOARD_H__

#include "Pos.h"
#include "Player.h"
#include <vector>

class Piece;

// 보드 상태 및 게임 로직 전체를 관리하는 클래스
class Board
{
    int rows, cols;
    std::vector<std::vector<Piece *>> board; // 말 포인터의 2차원 배열로 보드 상태 저장하기

public:
    Player players[2]; // 두 플레이어 정보 저장하기

    Board(int rows = 8, int cols = 8);
    ~Board();

    std::vector<std::vector<Piece *>> get_board() const;
    // 주어진 Pos가 보드의 유효한 범위 내에 있는지 확인하기
    bool is_in_range(Pos p) const;
    // 주어진 Pos에 있는 말 포인터 반환하기
    Piece *get(Pos p) const;
    // 주어진 Pos에 말 포인터 설정하기
    void set(Pos p, Piece *piece);
    // 주어진 Pos에 말이 없는지 확인하기
    bool is_empty(Pos p) const;
    // from에서 to로 말 이동 처리하기 (말 취하기 및 킹 승격 포함)
    int move(Pos from, Pos to);
    // 보드와 각 플레이어의 현재 상태 출력하기
    void print_board() const;
    // 게임 종료 조건 확인 후 승자 번호 반환하기
    // 게임이 아직 끝나지 않은 경우 -1 반환하기
    int game_over() const;
};

#endif
