#ifndef __AI_HPP__
#define __AI_HPP__

#include <iostream>
#include "../Pong/Controller.hpp"
#include "NeuralNetwork.hpp"
#include "Sensor.hpp"
#include "../definitions.hpp"

#include <string>

using namespace std;

class AI : public Controller {
friend class AITests;
private:
    Sensor* sensor;
    NeuralNetwork* nn;

    bool* movement;
public:

    AI(Sensor* sensor, NeuralNetwork* nn): Controller(SPEED), sensor(sensor), nn(nn) {
        movement = new bool[this->nn->get_params().inputs];
        for (unsigned i = 0; i < this->nn->get_params().inputs; ++i) {
            movement[i] = false;
        }
    }

    AI(Sensor* sensor, NetworkParams & params): Controller(SPEED), sensor(sensor) {
        nn = new NeuralNetwork(params);
        movement = new bool[params.inputs];
        for (unsigned i = 0; i < params.inputs; ++i) {
            movement[i] = false;
        }
    }

    AI(Sensor* sensor, NetworkParams & params, NeuralNetwork* nn1, NeuralNetwork* nn2, float mutation_rate):
    Controller(0), sensor(sensor) {
        //cout << "breeding network" << endl;
        nn1->forward_propagation();
        nn2->forward_propagation();

        nn = new NeuralNetwork(params, nn1, nn2, mutation_rate);
        //cout << "made network" << endl;
        movement = new bool[params.inputs];
        for (unsigned i = 0; i < params.inputs; ++i) {
            movement[i] = false;
        }
    }

    AI(Sensor* sensor, string directory): sensor(sensor) {
        nn = new NeuralNetwork(directory);
        movement = new bool[nn->num_inputs()];
        for (unsigned i = 0; i < nn->num_inputs(); ++i) {
            movement[i] = false;
        }
    }

    ~AI() {
        if(!sensor) delete sensor;
        if(!nn) delete nn;
        if(!movement) delete [] movement;
    }

    virtual NeuralNetwork* getNetwork() {
        return nn;
    }

    virtual float get_fitness() {
        unsigned total = 0;
        //cout << num_alive << ' ' << movement[0] << ' ' << movement[1] << ' ' << movement[2] << endl;
        for (unsigned i = 0; i < nn->get_params().inputs; ++i) {
            if (movement[i]) {
                ++total;
            }
        }

        return total;
    }

    virtual void move(Player* paddle) {
        sensor->set_activations(paddle, nn->get_inputs(), nn->num_inputs());
        //cout << "after setting activations" << endl;
        //std::cout << "moving" << std::endl;
        // float* test = nn->get_inputs();
        // for (unsigned i = 0; i < 7; ++i) {
        //     std::cout << test[i] << ' ';
        // }
        // std::cout << '\n';

        nn->forward_propagation();

        float * outputs = nn->get_outputs();

        unsigned index_max = 1;
        for (unsigned i = 0; i < NUM_OUTPUTS; ++i) {
            //std::cout << outputs[i] << ' ';
            if (outputs[i] > outputs[index_max]) {
                index_max = i;
            }
        }
        //std::cout << '\n';

        if (index_max == 0) {
            paddle->setY(paddle->getY()-speed);
        }
        else if (index_max == 1) {
            paddle->setY(paddle->getY()+speed);
        }
        movement[index_max] = true;
    }
};

#endif
