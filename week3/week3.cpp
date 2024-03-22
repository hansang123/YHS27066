#include <iostream>

int main() {
    const std::string colors[] = { "\x1b[30m", "\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m" };
    const std::string endColor = "\x1b[0m";

    std::cout << "화면에 그림을 그리는 프로그램입니다." << std::endl;
    std::cout << "학번: 349218347" << std::endl;
    std::cout << "이름: 본인 이름" << std::endl;
    std::cout << std::endl;

    while (true) {
        int objectCode;
        std::cout << "화면에 그릴 물체 코드를 입력하세요 (1-7, 0: 종료): ";
        std::cin >> objectCode;

        if (objectCode == 0) {
            std::cout << "프로그램을 종료합니다." << std::endl;
            break;
        }
        else if (objectCode >= 1 && objectCode <= 7) {
            std::cout << colors[objectCode - 1] << "화면에 그릴 물체입니다." << endColor << std::endl; // ANSI 색상 코드 출력
        }
        else {
            std::cout << "잘못된 입력입니다. 다시 입력하세요." << std::endl;
        }
    }

    return 0;
}