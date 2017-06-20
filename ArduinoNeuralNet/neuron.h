#ifndef  H_NEURON
#define H_NEURON

#include <StandardCplusplus.h>
#include <vector>
#include <cmath>

struct Neuron {

  // Output signal from current neuron
  double output;
  double action_potential = 0;

  // Bias value
  double bias = -1;

  // Bias weight/threshold
  double threshold = 0;

  // Weights
  std::vector<double> weights{};

  //backpropagating error
  double delta = 0;

  // Constructors
  Neuron(){};
  Neuron(std::vector<double> new_weights, double new_threshold):weights{new_weights}, threshold{new_threshold}{};

  // Calculates the action potential of the neuron and
  // applies the sigmoid activation function
  void activate(std::vector<double> inputs);
  inline unsigned short getNumberOfWeights() {return (weights.size());}

private:
  // Sigmoid activation function
  inline double sigmoid(double potential){return 1/(1 + exp(-potential));}
};

#endif
