#include <iostream>
#include "sdl2lib/include/SDL2/SDL.h"
#include "sdl2lib/include/SDL2/SDL_ttf.h"
#include "Text.hpp"

#ifdef __WIN32
#include <windows.h>
#define sleep(x) Sleep(x*1000)
#endif


int main(int argc, char * argv[]) {
    // initialize a window
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *screen = SDL_CreateWindow("My application",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            0);
    if(!screen) {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);
    if(!renderer) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    // present a black screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    cout << "Press ESCAPE to exit." << endl;

    // calling Text class to render a string
    Text* message = new Text(renderer, "hello world", "pixel.ttf", 100, {255, 255, 255, 255});
    message->set_text_size(50);
    message->set_text_pos(5);
    message->render_text();

    // keep window running until ESC is pressed
    bool running = true;
    SDL_Event event;
    while(running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                    break;
                }
                break;
            }
        }
    }

    // destroy the window when finished
    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}

//g++ main_text.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o test