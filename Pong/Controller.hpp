#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "sdl2lib/include/SDL2/SDL.h"
#include "../definitions.hpp"

class Player;
class NeuralNetwork;

class Controller {
protected:
    double speed;
public:
    Controller(double speed): speed(speed) {}

    Controller(): speed(SPEED) {}

    virtual void move(Player*) = 0;

    virtual ~Controller() {}

    virtual NeuralNetwork* getNetwork() { return nullptr; }
    virtual float get_fitness() { return -1; }
};
#endif
