//g++ main.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/program

//g++ Train.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/train

#include "sdl2lib/include/SDL2/SDL.h"
#include "sdl2lib/include/SDL2/SDL_ttf.h"

#include "Gamemode/Gamemode.hpp"
#include "Gamemode/Train.hpp"
#include "Gamemode/Play.hpp"


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <iostream>
#include <cstring>

using namespace std;

void SetColor(int);

char intro();

int main(int argc, char * argv[]) {

    char input = intro();

    Gamemode* game;
    if (input == '2') {
        game = new Train();
    }
    else if (input == '1') {
        game = new Play();
    }
    else {
        throw("unexpected entry");
    }

    system("CLS");

    bool running = true;
    while (running) {
        game->update(running);
    }

    delete game;
    SetColor(7);
    system("PAUSE");
    return 0;
}

char intro() {
    SetColor(7);
    cout << endl << endl;
    cout << "NEUROEVOLUTION OF FIXED TOPOLOGIES" << endl;
    cout << endl << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    cout << "authors: " << endl;
    SetColor(5);
    cout << "\tChristopher Vurbenova - Mouri" << endl << endl;
    cout << "\tTran Nguyen" << endl << endl;
    cout << "\tKevin Liang" << endl << endl;
    SetColor(7);
    cout << "-------------------------------------------------------------------------------------" << endl;

    cout << "This project demonstrates an artificial neural network's ability to learn how to play the game\nPONG. We demonstrate this process through neuro evolution. The structure of the network is\npredetermined, but can be altered in the file: defintions.hpp\n";
    cout << endl;
    const char* output = "Would you like to play against an already trained network, or train one yourself? Type \'1\'\nto play against an AI. Type \'2\' to train a network: ";

    for (unsigned i = 0; i < strlen(output); ++i) {
        cout << output[i];
        Sleep(20);
    }

    char input;
    cin >> input;
    while (input != '1' && input != '2') {
        cout << endl;
        SetColor(4);
        cout << "Unexpected input. Try Again" << endl << endl;
        SetColor(7);
        cout << output;
        cin >> input;
    }
    cout << endl;

    return input;
}

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
// Name         | Value
//              |
// Black        |   0
// Blue         |   1
// Green        |   2
// Cyan         |   3
// Red          |   4
// Magenta      |   5
// Brown        |   6
// Light Gray   |   7
// Dark Gray    |   8
// Light Blue   |   9
// Light Green  |   10
// Light Cyan   |   11
// Light Red    |   12
// Light Magenta|   13
// Yellow       |   14
// White        |   15


//g++ program.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/program

//g++ program.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/program