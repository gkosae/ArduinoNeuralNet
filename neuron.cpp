#include "neuron.h"
#include <random>

void Neuron::reshape(unsigned short number_of_inputs){
  weights = std::vector<double>(number_of_inputs);
  initialiseWeights();
}

void Neuron::initialiseWeights() {
 // Initialise all weights with a random number between -1 and 1
  for (double& weight : weights) {
      weight = -1 + 2*randomize();
  }

  threshold = -1 + 2*randomize();
}

void Neuron::activate(std::vector<double> inputs) {
    unsigned int number_of_inputs = inputs.size();
    action_potential = 0;

    for (unsigned int i = 0; i < number_of_inputs; ++i) {
      action_potential += (weights.at(i) * inputs.at(i));
    }

    // Add weighted bias
    action_potential += (bias * threshold);

    output = sigmoid(action_potential);
}

// helper function
// Returns a random double precision floating point number between 0 and 1
double randomize() {
  short min = 0;
  short max = 100;

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type>dist(min, max);
  double random_number = (double)dist(rng)/(double)max;
  return random_number;
}
