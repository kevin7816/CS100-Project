#ifndef __TRAIN_HPP__
#define __TRAIN_HPP__

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Gamemode.hpp"
#include "../Pong/Object.hpp"
#include "../Pong/Controller.hpp"
#include "../Pong/Player.hpp"
#include "../Pong/User.hpp"
#include "../Pong/Ball.hpp"
#include "../Pong/Text.hpp"
#include "../Pong/GameRenderer.hpp"
#include "../NeuralNetwork/Sensor.hpp"
#include "../NeuralNetwork/AI.hpp"
#include "../NeuralNetwork/NetworkHandler.hpp"

#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>

#include "../definitions.hpp"

using namespace std;

class Train: public Gamemode {
private:
    NetworkHandler * handler;
    Player* left_wall;

    bool render_toggle;

public:
    Train(): Gamemode(), render_toggle(true) {
        Controller* left_controller = new User(SDL_SCANCODE_W, SDL_SCANCODE_S);
        left_wall= new Player(left_controller, 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT),22);
        gameRend.add(left_wall);

        NetworkParams params(INPUTS, OUTPUTS, HIDDEN_LAYERS, HIDDEN_LAYER_SIZE);
        handler = new NetworkHandler(params, 0.05, 1200);
        handler->init_networks();

        handler->serve();
    }

    ~Train() {
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
            handler->save(num_input);
        }
        delete handler;
        delete left_wall;
    }

    virtual void update(bool & running) {
        lastFrame=SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)) {
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
        }

        Ball** balls = handler->getBalls();
        for (unsigned i = 0; i < handler->size(); ++i) {
            if (balls[i]) { //some balls are nullptr as players get killed
                update(balls[i]);
            }
        }
        handler->update();
        input(running);
        // left_wall->get_input();

        //render(frameCount, timerFPS, lastFrame, renderer, left_paddle, right_paddle, ball, message);
        if (render_toggle) {
            gameRend.render_all(renderer, frameCount, timerFPS, lastFrame, handler->getObjects());
        }
    }
private:
    void update(Ball* ball){
        SDL_Rect b1 = ball->getRect();
        SDL_Rect lp = left_wall->getRect();

        if(SDL_HasIntersection(&b1, &lp)){
            double rel= (left_wall->getY()+(left_wall->getH()/2))-(ball->getY()+8);
            double norm = rel/(left_wall->getH()/2);
            double bounce = norm * (5*PI/12);
            double num= (rand() % 360);
            ball->setVelX((ball->getSpeed()*1)*abs(cos(num))); //sends ball at different angle based on where the ball has hit the paddle
            ball->setVelY((ball->getSpeed())*sin(num));
        }

        if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);       //check to see if ball hit top or bottom walls
        ball->setX(ball->getVelX()+ball->getX());                                               //ball movement;
        ball->setY(ball->getVelY()+ball->getY());

        if(left_wall->getY()<0) left_wall->setY(0);                                                         // adds boundries for left paddle
        if(left_wall->getY() + left_wall->getH()>HEIGHT) left_wall->setY(HEIGHT-left_wall->getH());

        return;
    }

    void input(bool &running) {
        SDL_Event e;
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running = false;                          //allows for key inputs
        if(keystates[SDL_SCANCODE_ESCAPE]) {
            running = false;
        }
        if (keystates[SDL_SCANCODE_T]) {
            cout << "pressed" << endl;
            render_toggle = !render_toggle;
            while (keystates[SDL_SCANCODE_T]) {
                while(SDL_PollEvent(&e));
                keystates = SDL_GetKeyboardState(NULL);
            }
        }


        return;
    }
};

#endif
