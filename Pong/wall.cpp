#include <iostream>
#include "SDL2/SDL.h"
#include "Object.h"
#include "Player.h"
#include "Ball.h"

#include <ctime>
#include <math.h>

 int HEIGHT =720;
 int WIDTH = 1500;
 double SPEED =9.0;
 double PI = 3.14159265358979323846;


void render(int frameCount, int timerFPS, int lastFrame, SDL_Renderer *renderer, Player* left_paddle, Player* right_paddle, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     //renders black screen
    SDL_RenderClear(renderer);

    frameCount++;                                   // implements frame cap
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS<(1000/60)) {                        
        SDL_Delay((1000/60)-timerFPS);
    }
    left_paddle->show(renderer);                    // renders game objects
    right_paddle->show(renderer);
    ball->show(renderer);
}

void serve(Player* left_paddle, Player* right_paddle, Ball* ball, bool &turn){
    left_paddle->setY((HEIGHT/2)-(left_paddle->getH())/2);              //sets the paddles in place
    right_paddle->setY(left_paddle->getY()+5);
    if(turn) {
        ball->setX(left_paddle->getX()+(left_paddle->getW()*4));        //serves ball
        ball->setVelX(ball->getSpeed()/2);    
    }
    else{
        ball->setX(right_paddle->getX()+(right_paddle->getW()*4));
        ball->setVelX(ball->getSpeed()/-2);
    }
    ball->setVelY(0);
    ball->setY((HEIGHT/2)-8);
    turn=!turn;
}

void update(Player* left_paddle, Player* right_paddle, Ball* ball, bool &turn){
    SDL_Rect b1 = ball->getRect();
    SDL_Rect lp = left_paddle->getRect();
    SDL_Rect rp = right_paddle->getRect();
    if(SDL_HasIntersection(&b1, &rp)){                                                  //checks if ball and paddle interact
        double rel= (right_paddle->getY()+(right_paddle->getH()/2))-(ball->getY()+8);
        double norm = rel/(right_paddle->getH()/2);
        double bounce = norm * (5*PI/12);
        double num= (rand() % 100);
        // std::cout << "Right1: " << cos(num) << std::endl;
        // std::cout << "Right2: " << -sin(num) << std::endl;
        ball->setVelX((ball->getSpeed()*-1)*abs(cos(num)));                               //sends ball at different angle based on where the ball has hit the paddle
        ball->setVelY((ball->getSpeed())*-abs(sin(num)));
        // std::cout << "RightX " << ball->getVelX() << std::endl;
        // std::cout << "RightY " << ball->getVelY() << std::endl;
    }
    if(SDL_HasIntersection(&b1, &lp)){
        double rel= (left_paddle->getY()+(left_paddle->getH()/2))-(ball->getY()+8);
        double norm = rel/(left_paddle->getH()/2);
        double bounce = norm * (5*PI/12);
        // std::cout << "Left: " << cos(bounce) << std::endl;
        ball->setVelX((ball->getSpeed()*1)*cos(bounce));
        ball->setVelY((ball->getSpeed())*-sin(bounce));
        // std::cout << "LeftX " << ball->getVelX() << std::endl;
        // std::cout << "LeftY " << ball->getVelY() << std::endl;
    }
    if(ball->getX()<=0) serve(left_paddle, right_paddle, ball, turn);                                   //checks to see if ball has reacted the left or right side to score point
    if(ball->getX()+16>=WIDTH) serve(left_paddle, right_paddle, ball, turn);
    if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);       //check to see if ball hit top or bottom walls
    ball->setX(ball->getVelX()+ball->getX());                                               //ball movement;
    ball->setY(ball->getVelY()+ball->getY());

    if(left_paddle->getY()<0) left_paddle->setY(0);                                                         // adds boundries for left and right paddles
    if(left_paddle->getY() + left_paddle->getH()>HEIGHT) left_paddle->setY(HEIGHT-left_paddle->getH());
    if(right_paddle->getY()<0) right_paddle->setY(0);
    if(right_paddle->getY() + right_paddle->getH()>HEIGHT) right_paddle->setY(HEIGHT-right_paddle->getH());
}

void input(bool &running, Player* left_paddle, Player* right_paddle) {
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running = false;                          //allows for key inputs
    if(keystates[SDL_SCANCODE_ESCAPE]) running = false;
    if(keystates[SDL_SCANCODE_W]) left_paddle->setY(left_paddle->getY()-SPEED);
    if(keystates[SDL_SCANCODE_S]) left_paddle->setY(left_paddle->getY()+SPEED);
    if(keystates[SDL_SCANCODE_UP]) right_paddle->setY(right_paddle->getY()-SPEED);
    if(keystates[SDL_SCANCODE_DOWN]) right_paddle->setY(right_paddle->getY()+SPEED);
}


int main(int argc, char * argv[]) {
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
    bool running=1;
    bool turn=1;
    int frameCount, timerFPS, lastFrame, fps;
    static int lastTime=0;

    Player* left_paddle = new Player(32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
    Player* right_paddle = new Player(WIDTH-32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT),12);
    Ball* ball = new Ball();

    serve(left_paddle, right_paddle, ball, turn);

    // l_paddle.x=32; l_paddle.h=HEIGHT/4;
    // l_paddle.y=(HEIGHT/2)-(l_paddle.h/2);
    // l_paddle.w=12;

    while(running){
        lastFrame=SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)) {
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
        }
        update(left_paddle, right_paddle, ball, turn);
        input(running, left_paddle, right_paddle);
        render(frameCount, timerFPS, lastFrame, renderer, left_paddle, right_paddle, ball);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}

//g++ wall.cpp -ISDL2-mingw32\include -L SDL2-mingw32\lib -w -lmingw32 -lSDL2main -lSDL2 -o Wall


