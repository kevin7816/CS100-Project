# AI Learns to Play a Simple Game

 > Authors: 
 \<[Christopher Vurbenova-Mouri](https://github.com/Quidifer)\>
 \<[Hongting(Kevin) Liang](https://github.com/kevin7816)\>
 \<[Tran Nguyen](https://github.com/trannguyen28)\>

## Why is it important or interesting to you?
 This project is interesting because it explores the realm of AI. We find it interesting
that an algorithm can learn and adapt on its own using the evolutionary process


## Languages/Tools/Technologies
> (This list may change over the course of the project)
 * C++

 * SDL2 - SDL2 is a library that gives easy access to a visual interface that will display our game

 * Neural Network - A Neural Network is a very specific type of graph. It uses a mathematical operation called forward
 propagation to make decisions based upon inputs. \>

## What will be the input/output of your project?
 * This project mainly focuses on teaching AI to play a simple game, so our input would be the game Pong (we will implement it ourselves), and the output would be AI being able to play the game with a low percentage of losing.

# Design Patterns
 * Abstract Factory: The abstract factory will be used to construct and perform operations in the neural network. We will have an abstract class called Neural_Network. That class will construct multiple layers of the neural network. These layers will work together to perform the arithmetic operations behind forward propagation. The abstract class is used to call member layer member functions.

 * Observer: The observer design pattern would be used to create pause menus inside the games we make. We would have an object that works as a button that has other objects be dependent off of it. Once the button is clicked, the state of that object will change and all other objects dependent on it will also change in state.

 * Visitor: The visitor will be used for the start of our game. We will define a new operation that acts as a “game starter” which visits all objects with differing interfaces from our game classes and operates them. Using visitor avoids adding operations that are unrelated to individual objects.
