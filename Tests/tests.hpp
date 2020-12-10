#ifndef __TESTS_H__
#define __TESTS_H__

#include <windows.h>
#include <io.h>

class Tests {
    public:
        Tests() {}
        // virtual ~Tests() = 0;
        virtual void run_tests() = 0;
        int passed = 0;
        int failed = 0;
};
void SetColor(int ForgC) {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

#endif
