#ifndef  H_NEURON
#define H_NEURON

#include <vector>
#include <cmath>
#include <iostream>

struct Neuron {

  // Output signal from current neuron
  double output;
  double action_potential = 0;

  // Bias value
  const double bias = -1;

  // Bias weight/threshold
  double threshold = 0;

  // Weights
  std::vector<double> weights{};

  //backpropagating error
  double delta = 0;

  /*
   *  Constructor<br/>
   *  @args<br/>
   *    number_of_inputs: The number of inputs being fed into the neuron
   */
  Neuron(unsigned short number_of_inputs){reshape(number_of_inputs);}
  Neuron(){};

  // Reshapes the neuron by changing the number of inputs
  // being fed into the neurons. Also reshapes the weights and weight_diffs vectors
  void reshape(unsigned short number_of_inputs);

  // Calculates the action potential of the neuron and
  // applies the sigmoid activation function
  void activate(std::vector<double> inputs);

  // Derivative of the sigmoid activation function used for backpropagation
  inline double sigmoidPrime(){return exp(-action_potential)/pow(1 + exp(-action_potential), 2);}
  inline unsigned short getNumberOfWeights() {return (weights.size());}
  inline void setWeights(std::vector<double> new_weights) {weights = new_weights;}

private:
  // Initialises each weight value and threshold
  // with a random floating point number between -1 and 1
  void initialiseWeights();

  // Sigmoid activation function
  inline double sigmoid(double potential){return 1/(1 + exp(-potential));}
};

// helper function
// returns a random double precision floting point number between 0 and 1
double randomize();

#endif
