#ifndef __USER_HPP__
#define __USER_HPP__

#include "../definitions.hpp"

class User: public Controller {
private:
    unsigned up;
    unsigned down;
public:
    User(double speed, unsigned up, unsigned down):
    Controller(speed), up(up), down(down) {}

    User(unsigned up, unsigned down):
    Controller(SPEED), up(up), down(down) {}

    virtual void move(Player* paddle) {
        SDL_Event e;
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        if(keystates[up]) paddle->setY(paddle->getY()-speed);
        if(keystates[down]) paddle->setY(paddle->getY()+speed);
    }
};

#endif
