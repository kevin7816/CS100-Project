#include <iostream>
#include "SDL2/SDL.h"

#include <ctime>
#include <math.h>

 int HEIGHT =720;
 int WIDTH = 720;
 double SPEED =9.0;
 double PI = 3.14159265358979323846;
// SDL_Rect l_paddle;

class Object {
    private:
        double x;
        double y;
    public:
        object() {
            x=0.0;
            y=0.0;
        }
        object(double x, double y){
            this->x=x;
            this->y=y;
        }
};

class Player : public Object {
    private: 
        SDL_Rect rect;
    public: 
        Player(double x, double y, double h, double w){
            rect.x=x;
            rect.y=y;
            rect.h=h;
            rect.w=w;
        }
        double getH(){
            return rect.h;
        } 
        void setH(double h){
            rect.h=h;
        }
        double getX(){
            return rect.x;
        } 
        void setX(double x){
            rect.x=x;
        }
        double getY(){
            return rect.y;
        } 
        void setY(double y){
            rect.y=y;
        }
        double getW(){
            return rect.w;
        } 
        void setW(double w){
            rect.w=w;
        }
        void show(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        }
        SDL_Rect getRect(){
            return rect;
        }
        
};

class Ball : public Object {
    private:
        double speed=16.0;
        double velX=0;
        double velY=0;
        SDL_Rect rect;
    public:
        Ball(){
            rect.x=WIDTH/2;
            rect.y=HEIGHT;
            rect.h=16;
            rect.w=16;
        }
        Ball(double x, double y){
            rect.x=x;
            rect.y=y;
            rect.h=16;
            rect.w=16;
        }
        double getH(){
            return rect.h;
        } 
        void setH(double h){
            rect.h=h;
        }
        double getX(){
            return rect.x;
        } 
        void setX(double x){
            rect.x=x;
        }
        double getY(){
            return rect.y;
        } 
        void setY(double y){
            rect.y=y;
        }
        double getW(){
            return rect.w;
        } 
        void setW(double w){
            rect.w=w;
        }
        void setSpeed(double speed){
            this->speed=speed;
        }
        double getSpeed(){
            return speed;
        }
        void setVelX(double x){
            velX=x;
        }
        double getVelX(){
            return velX;
        }
        void setVelY(double y){
            velY=y;
        }
        double getVelY(){
            return velY;
        }
        void show(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderPresent(renderer);
        }
        SDL_Rect getRect(){
            return rect;
        }
        // bool collison(Player* paddle){
        //     SDL_Rect r1 = paddle->getRect();
        //     return SDL_HasIntersection(&rect, &r1);
        // }
};

void render(int frameCount, int timerFPS, int lastFrame, SDL_Renderer *renderer, Player* left_paddle, Player* right_paddle, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    frameCount++;
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS<(1000/60)) {
        SDL_Delay((1000/60)-timerFPS);
    }
    left_paddle->show(renderer);
    right_paddle->show(renderer);
    ball->show(renderer);
}

void serve(Player* left_paddle, Player* right_paddle, Ball* ball, bool &turn){
    left_paddle->setY((HEIGHT/2)-(left_paddle->getH())/2);
    right_paddle->setY(left_paddle->getY());
    if(turn) {
        ball->setX(left_paddle->getX()+(left_paddle->getW()*4));
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
    if(SDL_HasIntersection(&b1, &rp)){
        double rel= (right_paddle->getY()+(right_paddle->getH()/2))-(ball->getY()+8);
        double norm = rel/(right_paddle->getH()/2);
        double bounce = norm * (5*PI/12);
        ball->setVelX((ball->getSpeed()*-1)*cos(bounce));
        ball->setVelY((ball->getSpeed())*-sin(bounce));
    }
    if(SDL_HasIntersection(&b1, &lp)){
        double rel= (left_paddle->getY()+(left_paddle->getH()/2))-(ball->getY()+8);
        double norm = rel/(left_paddle->getH()/2);
        double bounce = norm * (5*PI/12);
        ball->setVelX((ball->getSpeed()*1)*cos(bounce));
        ball->setVelY((ball->getSpeed())*-sin(bounce));
    }
    if(ball->getX()<=0) serve(left_paddle, right_paddle, ball, turn); 
    if(ball->getX()+16>=WIDTH) serve(left_paddle, right_paddle, ball, turn);
    if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);
    ball->setX(ball->getVelX()+ball->getX());
    ball->setY(ball->getVelY()+ball->getY());

    if(left_paddle->getY()<0) left_paddle->setY(0);
    if(left_paddle->getY() + left_paddle->getH()>HEIGHT) left_paddle->setY(HEIGHT-left_paddle->getH());
    if(right_paddle->getY()<0) right_paddle->setY(0);
    if(right_paddle->getY() + right_paddle->getH()>HEIGHT) right_paddle->setY(HEIGHT-right_paddle->getH());
}

void input(bool &running, Player* left_paddle, Player* right_paddle) {
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running = false;
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
    Player* right_paddle = new Player(WIDTH-32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
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

}




