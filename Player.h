#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

// 플레이어의 이름, 번호, 획득한 말 수를 관리하는 클래스
class Player
{
    std::string name;  // 플레이어 이름 (대문자로 저장하기)
    int number;        // 플레이어 번호 (1 또는 2)
    int won_pieces;    // 현재까지 획득한 상대 말의 수

public:
    // 이름과 플레이어 번호를 설정하고 이름을 대문자로 변환하기
    Player(std::string name = "", int number = 0);
    // 플레이어 이름 반환하기
    std::string get_name() const;
    // 플레이어 번호 반환하기
    int get_number() const;
    // 획득한 말의 수 반환하기
    int get_won_pieces() const;
    // 이름을 설정하고 대문자로 변환하기
    void set_name(std::string n);
    // 플레이어 번호 설정하기 (1 또는 2만 허용)
    void set_number(int n);
    // 획득한 말 수를 1 증가시키기
    void add_win();
};

#endif
