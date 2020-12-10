#ifndef __PLAY_HPP__
#define __PLAY_HPP__

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

class Play: public Gamemode {
private:
    Player* opponent;
    Player* user;
public:
    Play(): Gamemode() {
        
    }
};

#endif
