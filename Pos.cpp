#include "Pos.h"
#include <cctype>

Pos::Pos(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Pos::get_x() const
{
    return x;
}

int Pos::get_y() const
{
    return y;
}

Pos Pos::interpret_coordinates(std::string coordinates)
{
    // 입력 형식: 2글자 문자열, (열)(행) 순서로 입력받기
    // (1) 알파벳 + 숫자
    // (2) 알파벳 + 알파벳 (행이 10 이상인 경우)

    // 길이가 2가 아닌 경우 유효하지 않은 좌표로 처리하기
    if (coordinates.length() != 2)
        return Pos(-1, -1);

    char col = toupper(coordinates[0]), row = toupper(coordinates[1]);
    // 열 문자를 0-based 인덱스로 변환하기 ('A' -> 0, 'B' -> 1, ...)
    int col_coordinate = col - 'A';
    int row_coordinate = -1;
    if ('0' <= row && row <= '9')
        row_coordinate = row - '0'; // 숫자 문자 -> 정수 변환하기
    else if ('A' <= row && row <= 'F')
        row_coordinate = row - 'A' + 10; // 알파벳 문자 -> 10 이상 정수 변환하기

    return Pos(row_coordinate, col_coordinate);
}
