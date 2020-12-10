#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

//------------------------------------------------------------------------------------------------------


//
// CONTROL OPTIONS
//
// controls begin with: "SDL_SCANCODE_" and end with the desired letter
// arrow keys: SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT
//
unsigned PLAYER_UP = SDL_SCANCODE_W;
unsigned PLAYER_DOWN = SDL_SCANCODE_S;
//


//
// GAME OPTIONS
//
// note: these values dont effect the game options for the predetermined
//       difficulties
double SPEED = 9.0;
double BALL_SPEED = 14;
//

//
// Evolutionary definitions
//
unsigned NUM_FITTEST = 20; //how many players are selected for breeding
unsigned NUM_RENDERED_AIS = 5; //how many players are rendered at a time
//


// NeuralNetwork definitions
//
// These are the definitions for the Neural Network's
// topology. We've only tested 4,3,1,5 and 3,3,1,5. We have
// not found success with drasticially different structures
// than those two.
//
const unsigned INPUTS = 3; //recommended to be 4 or 5
const unsigned OUTPUTS = 3; //dont change
const unsigned HIDDEN_LAYERS = 1;
const unsigned HIDDEN_LAYER_SIZE = 5;
//

//---------------------------------------------------------------------------------------------------------





//
// DONT CHANGE
//
const unsigned NUM_OUTPUTS = 3;
int HEIGHT = 720;
int WIDTH = 1280;
double PI = 3.14159265358979323846;

#endif
