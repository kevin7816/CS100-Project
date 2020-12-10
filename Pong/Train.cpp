#include <iostream>
#include "sdl2lib/include/SDL2/SDL.h"
#include "sdl2lib/include/SDL2/SDL_ttf.h"
#include "Object.hpp"
#include "Controller.hpp"
#include "Player.hpp"
#include "User.hpp"
#include "Ball.hpp"
#include "Text.hpp"
#include "GameRenderer.hpp"
#include "../NeuralNetwork/Sensor.hpp"
#include "../NeuralNetwork/AI.hpp"
#include "../NeuralNetwork/NetworkHandler.hpp"

#include <ctime>
#include <math.h>

#include "../definitions.hpp"


// this function is GameRenderer class
// void render(int frameCount, int timerFPS, int lastFrame, SDL_Renderer *renderer, Player* left_paddle, Player* right_paddle, Ball* ball, Text* message) {
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     //renders black screen
//     SDL_RenderClear(renderer);

//     frameCount++;                                   // implements frame cap
//     timerFPS = SDL_GetTicks()-lastFrame;
//     if(timerFPS<(1000/60)) {
//         SDL_Delay((1000/60)-timerFPS);
//     }
//     left_paddle->show(renderer);                    // renders game objects
//     right_paddle->show(renderer);
//     ball->show(renderer);

//     return;
// }

void update(Player* left_paddle, Ball* ball){
    SDL_Rect b1 = ball->getRect();
    SDL_Rect lp = left_paddle->getRect();

    if(SDL_HasIntersection(&b1, &lp)){
        double rel= (left_paddle->getY()+(left_paddle->getH()/2))-(ball->getY()+8);
        double norm = rel/(left_paddle->getH()/2);
        double bounce = norm * (5*PI/12);
        double num= (rand() % 360);
        // while (abs(sin(num)) > 0.7) {
        //     //cout << "do over" << endl;
        //     num= (rand() % 360);
        // }
        //ball->setVelX((ball->getSpeed()*1)*cos(bounce));
        //ball->setVelY((ball->getSpeed())*-sin(bounce));
        ball->setVelX((ball->getSpeed()*1)*abs(cos(num)));                               //sends ball at different angle based on where the ball has hit the paddle
        //ball->setVelY((ball->getSpeed())*abs(sin(num)));
        ball->setVelY((ball->getSpeed())*sin(num));
    }
    //if(ball->getX()<=0) handler.serve(ball);                                   //checks to see if ball has reacted the left or right side to score point
    if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);       //check to see if ball hit top or bottom walls
    ball->setX(ball->getVelX()+ball->getX());                                               //ball movement;
    ball->setY(ball->getVelY()+ball->getY());

    if(left_paddle->getY()<0) left_paddle->setY(0);                                                         // adds boundries for left paddle
    if(left_paddle->getY() + left_paddle->getH()>HEIGHT) left_paddle->setY(HEIGHT-left_paddle->getH());

    return;
}

void input(bool &running) {
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running = false;                          //allows for key inputs
    if(keystates[SDL_SCANCODE_ESCAPE]) {
        running = false;
    }

    return;
}


int main(int argc, char * argv[]) {
    srand(time(0));

    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not init SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Pong",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,0);
    if(!window) {
        fprintf(stderr, "Could not create window\n");
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(!renderer) {
        fprintf(stderr, "Could not create renderer\n");
        return 1;
    }

    // create GameRenderer
    GameRenderer gameRend;

    // Pong Game
    bool running=1;
    int frameCount, timerFPS, lastFrame, fps;
    static int lastTime=0;

    Controller* left_controller = new User(SDL_SCANCODE_W, SDL_SCANCODE_S);
    Player* left_paddle = new Player(left_controller, 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT),12); //height / 4 if actual paddle;
    gameRend.add(left_paddle);

    NetworkParams params(4,3,1,5);
    NetworkHandler handler(params, 0.05, 1200);
    handler.init_networks();

    handler.serve();

    // l_paddle.x=32; l_paddle.h=HEIGHT/4;
    // l_paddle.y=(HEIGHT/2)-(l_paddle.h/2);
    // l_paddle.w=12;

    // render static Text
    // Text* message = new Text("Press ESCAPE to exit", 50);
    // message->create_text(renderer);
    // message->set_text_pos(300, 0); // settings related to the text's position needs to be called after create()
    // // message->show(renderer);       // renders text
    // gameRend.add(message);


    while(running){
        lastFrame=SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)) {
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
        }
        Ball** balls = handler.getBalls();
        for (unsigned i = 0; i < handler.size(); ++i) {
            if (balls[i]) { //some balls are nullptr as players get killed
                update(left_paddle, balls[i]);
            }
        }
        handler.update();
        //cout << "jasldfjlk" << endl;
        input(running);
        left_paddle->get_input();

        //render(frameCount, timerFPS, lastFrame, renderer, left_paddle, right_paddle, ball, message);
        if (handler.get_nth_generation() % 500 == 0 || handler.get_nth_generation() == 1) {
            gameRend.render_all(renderer, frameCount, timerFPS, lastFrame, handler.getObjects());
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    char input = 0;
    while (input != 'y' && input != 'n') {
        cout << "would you like to save? y/n: " << endl;
        cin >> input;
        cout << endl;
    }
    if (input == 'y') {
        unsigned num_input = -1;
        while (num_input < 0 ||  num_input > NUM_FITTEST) {
            cout << "How many networks would you like to save? Upper Limit: " << NUM_FITTEST << endl;
            cin >> num_input;
            cout << endl;
        }
        handler.save(num_input);
    }

    system("PAUSE");

    return 0;
}

//g++ pong.cpp -Isdl2lib\include -Lsdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/test
//g++ pong.cpp -I..\sdl2lib\include -L..\sdl2lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o ../compile/test

//g++ Train.cpp -I..\SDL2-mingw32\include -L ..\SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o ../compile/train

//g++ Train.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -o compile/train
