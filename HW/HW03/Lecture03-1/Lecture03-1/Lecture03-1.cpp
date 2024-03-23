#include <iostream>
#include <bitset>

using namespace std;

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    /** 흰색 블록을 그리는 키코드 : 1 (1)
    * 빨강색 블록을 그리는 키코드 : 2 (10)
    * 녹색 블록을 그리는 키코드 : 4 (100)
    * 노란색 블록을 그리는 키코드 : 8 (1000)
    * 청록색 블록을 그리는 키코드 : 16 (10000)
    * 마젠타색 블록을 그리는 키코드 : 32 (100000)*/
};

void drawBlock(int code) {
    // 흰(37), 빨(31), 녹(32), 노(33), 청(36), 마(35) 순으로 정렬
    switch (code) {
    case 1:
        cout << "\x1b[37m" << "입력하신 코드의 색상입니다";
        break;
    case 2:
        cout << "\x1b[31m" << "입력하신 코드의 색상입니다";
        break;
    case 4:
        cout << "\x1b[32m" << "입력하신 코드의 색상입니다";
        break;
    case 8:
        cout << "\x1b[33m" << "입력하신 코드의 색상입니다";
        break;
    case 16:
        cout << "\x1b[36m" << "입력하신 코드의 색상입니다";
        break;
    case 32:
        cout << "\x1b[35m" << "입력하신 코드의 색상입니다";
        break;
    case 64:
        cout << "\x1b[0m" << "코드를 종료합니다";
        exit(0);
    default:
        cout << "입력하신 코드의 색상입니다";
    }
}

int main() {
    cout << "화면에 그림을 그리는 프로그램입니다.\n";
    cout << "학번: 202127047\n";
    cout << "이름: 김수민\n";

    while (true) {
        int code;
        cout << "\n화면에 그릴 물체 코드를 입력하세요: ";
        cin >> code; // 값을 입력 받음

        cout << "2진수 변환: " << bitset<8>(code) << endl; // bitset을 이용해 입력받은 10진수를 8비트 사이즈로 변환하여 2진수로 변환

        drawBlock(code); // 입력받은 값을 이용하는 함수 호출
    }

    return 0;
}
