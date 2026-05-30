#ifndef __POS_H__
#define __POS_H__
#include <iostream>

// 보드 위의 좌표(행·열)를 저장하는 클래스
class Pos
{
    int x, y; // x: 행 인덱스, y: 열 인덱스

public:
    Pos(int x = 0, int y = 0);
    // 행 인덱스 반환하기
    int get_x() const;
    // 열 인덱스 반환하기
    int get_y() const;

public:
    // 문자열 좌표를 Pos 인스턴스로 변환하기
    static Pos interpret_coordinates(std::string coordinate);
};

#endif
