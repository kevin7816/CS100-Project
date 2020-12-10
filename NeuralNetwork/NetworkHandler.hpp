#ifndef __NETWORK_HANDLER_H__
#define __NETWORK_HANDLER_H__

#include "NeuralNetwork.hpp"
#include "../Pong/Ball.hpp"
#include "../Pong/Player.hpp"
#include "Sensor.hpp"
#include "AI.hpp"

#include <ctime>
#include <vector>
#include <math.h>
#include <utility>      // std::pair, std::make_pair
#include <string>
#include <fstream>

using namespace std;

float HEIGHT_RATIO = 8;

bool has(vector<unsigned> v, unsigned item);
float fRand(float fMin, float fMax);

class NetworkHandler {
private:
    NetworkParams network_params;
    float mutation_rate;
    unsigned generation_size;

    vector<unsigned> rendered_indices;
    vector<pair<NeuralNetwork*, float>> best_networks; // pair<neural_net, fitness
    unsigned num_alive;
    unsigned prev_alive;

    Ball** balls;
    Player** players; //player holds ais

    float fittest;
    unsigned num_generations;

public:
    NetworkHandler(unsigned inputs, unsigned outputs, unsigned hidden_layers, unsigned hidden_layer_size, float mutation_rate, unsigned generation_size):
    mutation_rate(mutation_rate), generation_size(generation_size), num_alive(generation_size), prev_alive(0), fittest(0), num_generations(0) {
        network_params.inputs = inputs;
        network_params.outputs = outputs;
        network_params.hidden_layers = hidden_layers;
        network_params.hidden_layer_size = hidden_layer_size;
    }

    NetworkHandler(NetworkParams & params, float mutation_rate, unsigned generation_size):
    NetworkHandler(params.inputs, params.outputs, params.hidden_layers, params.hidden_layer_size, mutation_rate, generation_size) {}

    void init_networks() {
        balls = new Ball*[generation_size];
        players = new Player*[generation_size];
        for (unsigned i = 0; i < generation_size; ++i) {
            balls[i] = new Ball();
            players[i] = new Player(new AI(new Sensor(balls[i]), network_params), 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/HEIGHT_RATIO),12);
            players[i]->randomize_color();
            balls[i]->set_color(players[i]->get_color());
        }

        for (unsigned i = 0; i < NUM_RENDERED_AIS; ++i) { //only render the first 5 players
            rendered_indices.push_back(i);
        }
        ++num_generations;
    }

    void update() {
        for (unsigned i = 0; i < generation_size; ++i) {
            if (players[i] && balls[i]) {
                //cout << "input " << i << endl;
                players[i]->get_input();
                //cout << "got input" << endl;
                update(players[i], balls[i]);
            }
        }
        if (clock() % 50 == 0 && num_alive != prev_alive) {
            //system("CLS");
            cout << "num alive: " << num_alive << endl;
            prev_alive = num_alive;
        }

        if (num_alive == 0) {
            clear();
            system("CLS");

            cout << "most fit: " << fittest << endl;
            for (unsigned i = 0; i < best_networks.size(); ++i) {
                if (best_networks.at(i).second > fittest) {
                    fittest = best_networks.at(i).second;
                }
            }
            cout << "most fit: " << fittest << endl;
            cout << "breeding a new generation" << endl;
            breed_new_generation();
            cout << "this is generation #" << num_generations << endl;
            for (unsigned i = 0; i < NUM_RENDERED_AIS; ++i) { //only render the first 5 players
                rendered_indices.push_back(i);
            }
            //cout << "breeding a new generation" << endl;
            serve();
        }
    }

    Ball** getBalls() {
        return balls;
    }
    unsigned size() {
        return generation_size;
    }

    vector<Object*> getObjects() {
        vector<Object*> objects;
        for (unsigned i = 0; i < rendered_indices.size(); ++i) {
            unsigned index = rendered_indices.at(i);
            if (players[index]) {
                objects.push_back(players[index]);
                objects.push_back(balls[index]);
            }
            else {
                for (unsigned j = 0; j < generation_size; ++j) {
                    if (!has(rendered_indices, j) && players[j]) {
                        rendered_indices.at(i) = j;
                    }
                }
            }
        }
        return objects;
    }

    void serve() {
        for (unsigned i = 0; i < generation_size; ++i) {
            players[i]->setX(WIDTH-32);

            // balls[i]->setX(players[i]->getX()+(players[i]->getW()*4));
            balls[i]->setX(players[i]->getX()-(players[i]->getW()*4 + 200));
            balls[i]->setVelX(balls[i]->getSpeed()/-2);

            balls[i]->setVelY(0);
            balls[i]->setY((HEIGHT/2)-8);
        }
    }

    unsigned get_nth_generation() {
        return num_generations;
    }

    void save(unsigned num_saves) {
        string file_name;
        if (num_saves > 1) {
            wstring new_folder(L"../saves/save_state_");
            srand(summnation());
            unsigned ID_SIZE = 10;
            for (unsigned i = 0; i < ID_SIZE; ++i) {
                if (rand() % 2 == 0) {
                    new_folder += rand() % 26 + 'a';
                }
                else {
                    new_folder += rand() % 10 + '0';
                }
            }
            if (_wmkdir(new_folder.c_str()) == -1) {
                cout << "could not create new directory" << endl;
            }
            string temp(new_folder.begin(), new_folder.end());
            file_name += temp;
            file_name += "/";
        }
        else {
            file_name += "../../saves/";
        }
        for (unsigned i = 0; i < num_saves; ++i) {
            int score = best_networks.at(i).second-3;
            if (score < 0) score = 0;
            best_networks.at(i).first->save(file_name, score);
        }
        srand(time(0));
    }
private:
    void update(Player* paddle, Ball* ball) {
        SDL_Rect b = ball->getRect();
        SDL_Rect p = paddle->getRect();
        if(SDL_HasIntersection(&b, &p)) {                                                  //checks if ball and paddle interact
            double rel = (paddle->getY()+(paddle->getH()/2))-(ball->getY()+8);
            double norm = rel/(paddle->getH()/2);
            double bounce = norm * (5*PI/12);
            ball->setVelX((ball->getSpeed()*-1)*cos(bounce));                               //sends ball at different angle based on where the ball has hit the paddle
            ball->setVelY((ball->getSpeed())*-sin(bounce));
            if (paddle->getY() != paddle->get_previousY()) {
                paddle->increment_fittness();
            }
            paddle->set_previousY(paddle->getY());
        }

        if(ball->getY()<=0 || ball->getY()+16>=HEIGHT) ball->setVelY(ball->getVelY()*-1);       //check to see if ball hit top or bottom walls
        ball->setX(ball->getVelX()+ball->getX());                                               //ball movement;
        ball->setY(ball->getVelY()+ball->getY());

        if(paddle->getY()<0) paddle->setY(0);                                       // boundaries for paddles
        if(paddle->getY() + paddle->getH()>HEIGHT) paddle->setY(HEIGHT-paddle->getH());

        if(ball->getX()+16>=WIDTH) kill(paddle, ball);
    }

    void kill(Player* paddle, Ball* ball) {
        float fitness = paddle->get_fitness();
        if (fitness < 50) {
            fitness += paddle->getController()->get_fitness();
        }
        if (best_networks.size() < NUM_FITTEST) {
            NeuralNetwork* nn = new NeuralNetwork((paddle->getController()->getNetwork()), network_params);
            best_networks.push_back(make_pair(nn, fitness));
        }
        else {
            for (unsigned i = 0; i < best_networks.size(); ++i) {
                if (*best_networks.at(i).first == *paddle->getController()->getNetwork()) {
                    if (fitness > best_networks.at(i).second) {
                        best_networks.at(i).second = fitness;
                    }
                    //if (fitness > 100) best_networks.at(i).second = (best_networks.at(i).second + fitness) / 2.0;
                    //else best_networks.at(i).second -= 0.1;
                    break;
                }
                if (best_networks.at(i).second <= fitness) {
                    //cout << best_networks.size() << endl;
                    //cout << fitness << " saving network" << endl;
                    NeuralNetwork* nn = new NeuralNetwork((paddle->getController()->getNetwork()), network_params);

                    if (best_networks.at(i).first) {
                        delete best_networks.at(i).first;
                    }
                    best_networks.at(i) = make_pair(nn, fitness);
                    break;
                }
            }
        }
        if (fittest < fitness) {
            fittest = fitness;
        }
        //cout << "save finished" << endl;

        for (unsigned i = 0; i < generation_size; ++i) {
            if (players[i] == paddle) {

                delete players[i];
                delete balls[i];

                players[i] = nullptr;
                balls[i] = nullptr;
                break;
            }
        }
        --num_alive;
    }

    void clear() {
        for (unsigned i = 0; i < generation_size; ++i) {
            if (balls[i]) {
                // cout << "asdjfklasfasdf" << endl;
                delete balls[i];
            }
            if (players[i]) {
                // cout << "asdnfjasjdfkl" << endl;
                delete players[i];
            }
        }
        delete [] balls;
        delete [] players;
        rendered_indices.clear();
    }

    void breed_new_generation() {
        // for (unsigned i = 0; i < best_networks.size(); ++i) {
        //     best_networks.at(i).first->forward_propagation();
        // }

        cout << best_networks.size() << endl;
        ++num_generations;
        balls = new Ball*[generation_size];
        players = new Player*[generation_size];
        for (unsigned i = 0; i < generation_size; ++i) {
            balls[i] = new Ball();
            if (i < best_networks.size()) {
                players[i] = new Player(new AI(new Sensor(balls[i]), new NeuralNetwork(best_networks.at(i).first, network_params)), 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/HEIGHT_RATIO),12);
            }
            else if (i % 3 == 0) {
                unsigned mutation_index = fRand(0, best_networks.size()-0.1);

                if (best_networks.at(mutation_index).second < 15) {
                    players[i] = new Player(new AI(new Sensor(balls[i]), new NeuralNetwork(network_params)), 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/HEIGHT_RATIO),12);
                }
                else {
                    AI* child = new AI(new Sensor(balls[i]), network_params, best_networks.at(mutation_index).first, best_networks.at(mutation_index).first, mutation_rate);
                    players[i] = new Player(child, 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/HEIGHT_RATIO),12);
                }
            }
            else {
                unsigned dad_index = fRand(0, best_networks.size()-1);
                unsigned mom_index = fRand(0, best_networks.size()-1);

                AI* child = new AI(new Sensor(balls[i]), network_params, best_networks.at(dad_index).first, best_networks.at(mom_index).first, mutation_rate);
                child->getNetwork()->forward_propagation();
                players[i] = new Player(child, 32,(HEIGHT/2)-(HEIGHT/8),(HEIGHT/HEIGHT_RATIO),12);
            }
            players[i]->randomize_color();
            players[i]->randomize_color();
            balls[i]->set_color(players[i]->get_color());
        }

        for (unsigned i = 0; i < best_networks.size(); ++i) {
            best_networks.at(i).second -= 0.1;
        }

        rendered_indices.clear();
        fittest = 0;
        num_alive = generation_size;
    }

    int summnation() {
        float summnation = 0;
        for (unsigned i = 0; i < best_networks.size(); ++i) {
            summnation += best_networks.at(i).second;
        }
        return summnation;
    }
};

bool has(vector<unsigned> v, unsigned item) {
    for (unsigned i = 0; i < v.size(); ++i) {
        if (v.at(i) == item) {
            return true;
        }
    }
    return false;
}

float fRand(float fMin, float fMax) {
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

#endif
