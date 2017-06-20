#include "neuron.h"

void Neuron::activate(std::vector<double> inputs) {
    unsigned int number_of_inputs = inputs.size();
    action_potential = 0;

    for (unsigned int i = 0; i < number_of_inputs; i++) {
      action_potential += (weights.at(i) * inputs.at(i));
    }

    // Add weighted bias
    action_potential += (bias * threshold);

    output = sigmoid(action_potential);
}
