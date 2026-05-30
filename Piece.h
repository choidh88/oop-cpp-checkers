#ifndef __PIECE_H__
#define __PIECE_H__

#include "Pos.h"
#include <iostream>

class Board;

// 모든 말의 공통 속성과 인터페이스를 정의하는 추상 기반 클래스
class Piece
{
protected:
    int player_number; // 이 말을 소유한 플레이어 번호 (1 또는 2)
    bool is_king;      // 킹 여부

public:
    Piece(int num, bool is_king);
    virtual ~Piece() = default;
    // 플레이어 번호와 말 종류(일반/킹)에 따른 표시 문자 반환하기
    virtual char get_symbol() const = 0;
    // 이 말을 소유한 플레이어 번호 반환하기
    int get_player_number() const;
    // 킹 말인지 확인하기
    bool is_king_piece() const;
    // from 좌표에서 to 좌표로 이동 가능한지 확인하기
    virtual bool can_move(Board &board, Pos from, Pos to) const = 0;
};

// 일반 말: 대각선 1칸 이동 또는 2칸 점프만 가능한 클래스
class Man : public Piece
{
public:
    Man(int num);
    // 플레이어 번호에 따른 소문자 표시 문자 반환하기
    char get_symbol() const override;
    // from 좌표에서 to 좌표로 이동 가능한지 확인하기
    bool can_move(Board &board, Pos from, Pos to) const override;
};

// 킹 말: 거리 제한 없이 대각선 이동이 가능한 클래스
class King : public Piece
{
public:
    King(int num);
    // 플레이어 번호에 따른 대문자 표시 문자 반환하기
    char get_symbol() const override;
    // from 좌표에서 to 좌표로 이동 가능한지 확인하기
    bool can_move(Board &board, Pos from, Pos to) const override;
};

#endif
