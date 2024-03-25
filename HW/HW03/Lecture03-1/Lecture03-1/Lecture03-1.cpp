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
    White = 37
};

void drawBlock(int code) {
    // 흰(37), 빨(31), 녹(32), 노(33), 청(36), 마(35) 순으로 정렬
    switch (code) {
    case 1:
        cout << "\x1b[37m" << "입력하신 코드의 색상입니다";
        break;
    case 10:
        cout << "\x1b[31m" << "입력하신 코드의 색상입니다";
        break;
    case 100:
        cout << "\x1b[32m" << "입력하신 코드의 색상입니다";
        break;
    case 1000:
        cout << "\x1b[33m" << "입력하신 코드의 색상입니다";
        break;
    case 10000:
        cout << "\x1b[36m" << "입력하신 코드의 색상입니다";
        break;
    case 100000:
        cout << "\x1b[35m" << "입력하신 코드의 색상입니다";
        break;
    case 1000000:
        cout << "\x1b[0m" << "코드를 종료합니다";
        exit(0);
    default:
        cout << "입력하신 코드의 색상입니다";
    }
}

int Convertnumber(int num) {
    int result = 0;
    int digit = 1; // 2진수 자릿수의 가중치
    while (num > 0) {
        int binary = num % 2; // 현재 자릿수의 2진수 값 계산
        result += binary * digit; // 계산된 값에 가중치를 곱하여 더함
        num /= 2; // 다음 자릿수로 이동
        digit *= 10; // 다음 자릿수의 가중치 증가
    }
    return result; // 변환된 값을 반환
}


int main() {
    /*
    * 흰색 블록을 그리는 키코드 : 1 (1)
    * 빨강색 블록을 그리는 키코드 : 2 (10)
    * 녹색 블록을 그리는 키코드 : 4 (100)
    * 노란색 블록을 그리는 키코드 : 8 (1000)
    * 청록색 블록을 그리는 키코드 : 16 (10000)
    * 마젠타색 블록을 그리는 키코드 : 32 (100000)
    * 프로그램 종료 : 64 (1000000)
    *
    * 프로그램을 시작하면 아래와 같이 쓰시오
    *
    *
    * 화면에 그림을 그리는 프로그램입니다.
    * 학번 : 349218347(본인학번)
    * 이름 : 본인이름
    *
    * 화면에 그릴 물체코드를 입력하세요 :
    * (반복)
    */
    cout << "화면에 그림을 그리는 프로그램입니다.\n";
    cout << "학번: 202127047\n";
    cout << "이름: 김수민\n";

    while (true) {
        int code;
        cout << "\n화면에 그릴 물체 코드를 입력하세요: ";
        cin >> code; // 값을 입력 받음

        code = Convertnumber(code); // 변환된 값을 저장
        //cout << code; // 진수 변환 확인
        drawBlock(code); // 변환된 값을 drawBlock 함수에 전달하여 출력
    }

    return 0;
}
