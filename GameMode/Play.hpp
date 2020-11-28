#ifndef __PLAY_H__
#define __PLAY_H__


#include "../Pong/sdl2lib/include/SDL2/SDL.h"
#include "../definitions.hpp"

#include "GameMode.hpp"
#include "../Pong/GameRenderer.hpp"
#include "../Pong/Player.hpp"
#include "../Pong/Ball.hpp"
#include "../Pong/Text.hpp"
#include "../Pong/Text.hpp"
#include "../Pong/User.hpp"

#include <iostream>
#include <cmath>

class Play : public GameMode {
    private:
        GameRenderer gameRend;
        Controller* left_controller;
        Player* left_paddle;
        Controller* right_controller;
        Player* right_paddle;
        Ball* ball;

    public:
        Play() : GameMode() {}

        // create game objects
        void setup(SDL_Renderer* renderer) {
            // set up left user player
            left_controller = new User(SDL_SCANCODE_W, SDL_SCANCODE_S);
            left_paddle = new Player(left_controller, 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
            left_paddle->randomize_color();

            // set up right user player
            right_controller = new User(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
            right_paddle = new Player(right_controller, WIDTH-32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/4),12);
            right_paddle->randomize_color();

            // set up ball
            ball = new Ball();

            // set up texts 
            Text* message = new Text("Press ESCAPE to exit", 50);
            message->create_text(renderer);
            message->set_text_pos(300, 0); // settings related to the text's position needs to be called after create()

            // add all created game objects to gameRend for rendering
            gameRend.add(left_paddle);
            gameRend.add(right_paddle);
            gameRend.add(ball);
            gameRend.add(message);

            return;
        }

        // render all objects on screen and run the game
        void run_game(SDL_Renderer* renderer) {
            bool running = 1;
            bool turn = 0;
            int frameCount, timerFPS, lastFrame, fps;
            static int lastTime = 0;

            serve(turn);

            while(running){
                lastFrame = SDL_GetTicks();
                if(lastFrame >= (lastTime + 1000)) {
                    lastTime = lastFrame;
                    fps = frameCount;
                    frameCount = 0;
                }
                update(turn);
                input(running);
                left_paddle->get_input();
                right_paddle->get_input();
                gameRend.render_all(renderer, frameCount, timerFPS, lastFrame);
            }

            return;
        }

    private:
        void serve(bool &turn){
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

            return;
        }

        void update(bool &turn){
            SDL_Rect b1 = ball->getRect();
            SDL_Rect lp = left_paddle->getRect();
            SDL_Rect rp = right_paddle->getRect();
            if(SDL_HasIntersection(&b1, &rp)){                                                  //checks if ball and paddle interact
                double rel = (right_paddle->getY()+(right_paddle->getH()/2))-(ball->getY()+8);
                double norm = rel/(right_paddle->getH()/2);
                double bounce = norm * (5*PI/12);
                ball->setVelX((ball->getSpeed()*-1)*cos(bounce));                               //sends ball at different angle based on where the ball has hit the paddle
                ball->setVelY((ball->getSpeed())*-sin(bounce));
            }
            if(SDL_HasIntersection(&b1, &lp)){
                double rel= (left_paddle->getY()+(left_paddle->getH()/2))-(ball->getY()+8);
                double norm = rel/(left_paddle->getH()/2);
                double bounce = norm * (5*PI/12);
                ball->setVelX((ball->getSpeed()*1)*cos(bounce));
                ball->setVelY((ball->getSpeed())*-sin(bounce));
            }
            if(ball->getX()<=0) serve(turn);                                   //checks to see if ball has reacted the left or right side to score point
            if(ball->getX()+16>=WIDTH) serve(turn);
            if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);       //check to see if ball hit top or bottom walls
            ball->setX(ball->getVelX()+ball->getX());                                               //ball movement;
            ball->setY(ball->getVelY()+ball->getY());

            if(left_paddle->getY()<0) left_paddle->setY(0);                                                         // adds boundries for left and right paddles
            if(left_paddle->getY() + left_paddle->getH()>HEIGHT) left_paddle->setY(HEIGHT-left_paddle->getH());
            if(right_paddle->getY()<0) right_paddle->setY(0);
            if(right_paddle->getY() + right_paddle->getH()>HEIGHT) right_paddle->setY(HEIGHT-right_paddle->getH());

            return;
        }

        void input(bool &running) {
            SDL_Event e;
            const Uint8 *keystates = SDL_GetKeyboardState(NULL);
            while (SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running = false;                          //allows for key inputs
            if(keystates[SDL_SCANCODE_ESCAPE]) running = false;

            return;
        }
};

#endif
