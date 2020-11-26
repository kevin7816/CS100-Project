#ifndef __AI_HPP__
#define __AI_HPP__

#include <iostream>
#include "../Pong/Controller.hpp"
#include "NeuralNetwork.hpp"
#include "Sensor.hpp"
#include "../definitions.hpp"


class AI: public Controller {
private:
    Sensor* sensor;
    NeuralNetwork* nn;
public:

    AI(Sensor* sensor, NeuralNetwork* nn): Controller(SPEED), sensor(sensor), nn(nn) {}

    AI(Sensor* sensor, NetworkParams & params): Controller(SPEED), sensor(sensor) {
        nn = new NeuralNetwork(params);
    }

    AI(Sensor* sensor, NetworkParams & params, NeuralNetwork* nn1, NeuralNetwork* nn2, float mutation_rate):
    Controller(0), sensor(sensor) {
        nn = new NeuralNetwork(params, nn1, nn2, mutation_rate);
    }

    virtual void move(Player* paddle) {
        sensor->set_activations(paddle, nn->get_inputs(), nn->num_inputs());

        // float* test = nn->get_inputs();
        // for (unsigned i = 0; i < 7; ++i) {
        //     std::cout << test[i] << ' ';
        // }
        // std::cout << '\n';

        nn->forward_propagation();
        float * outputs = nn->get_outputs();

        unsigned index_max = 0;
        for (unsigned i = 0; i < NUM_OUTPUTS; ++i) {
            std::cout << outputs[i] << ' ';
            if (outputs[i] > outputs[index_max]) {
                index_max = i;
            }
        }
        std::cout << '\n';

        if (index_max == 0) {
            paddle->setY(paddle->getY()-speed);
        }
        else if (index_max == 1) {
            paddle->setY(paddle->getY()+speed);
        }
    }
};

#endif
