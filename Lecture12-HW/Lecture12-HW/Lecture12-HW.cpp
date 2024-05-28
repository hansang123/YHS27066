#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    int count = 0;
    chrono::steady_clock::time_point now;  // now 변수를 함수 시작 부분에서 선언

    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    while (count < 10)
    {
        this_thread::sleep_for(chrono::milliseconds(1000) - chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start));

        count++;

        now = chrono::steady_clock::now();  // now 변수에 현재 시간 할당
        chrono::steady_clock::duration diff = now - start;
        int duration_ms = chrono::duration_cast<chrono::milliseconds>(diff).count();

        cout << "Count: " << count << " (Elapsed time: " << duration_ms << " ms)" << endl;

        start = now;
    }

    return 0;
}


