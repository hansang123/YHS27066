#include <iostream>
#include <bitset>
#include <Windows.h>
#include <vector>
using namespace std;


enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Cyan = 36,
    Magenta = 35,
    White = 37,
};

void setColor(int color) {
    cout << "\x1b[" << color << "m";
}

int main() {
    int input;

    std::cout << "화면에 그림을 그리는 프로그램입니다.\n";
    std::cout << "학번 : 202127066 \n";
    std::cout << "이름 : 유한상 \n";


    while (true) {
        // 사용자로부터 숫자를 입력 받음
        cout << "화면에 그릴 물체코드를 입력하세요 : ";
        cin >> input;

        if (input == 64) {
            cout << "프로그램을 종료." << endl;
            break;
        }

        // 입력된 숫자를 이진수로 변환
        bitset<6> binary(input);

        // 이진수 출력


        // 각 비트에 대응하는 색상을 배열로 저장
        int colors[] = { White, Red, Green, Yellow, Cyan, Magenta };

        // 각 자리의 값(비트)를 저장할 벡터 생성
        vector<int> bits;

        // 이진수의 각 자리에 대한 값을 벡터에 저장
        for (int i = 0; i < binary.size(); ++i) {
            bits.push_back(binary[i]);
        }

        // 이진수의 각 자리에 대한 색상을 입혀서 출력

        for (int i = 0; i < bits.size(); ++i) {
            int color;
            if (bits[i]) {
                // 해당 비트가 1이면 해당하는 색상으로 출력
                color = colors[i];
            }
            else {
                // 해당 비트가 0이면 기본 색상 출력
                color = Default;
            }
            setColor(color);
            cout << bits[i] << "";
        }
        cout << "\x1b[0m" << endl; // 색상 리셋
    }

    return 0;
}
