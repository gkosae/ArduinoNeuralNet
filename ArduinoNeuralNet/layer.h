#ifndef H_LAYER
#define H_LAYER

#include <StandardCplusplus.h>
#include <vector>
#include "neuron.h"


struct Layer {
  std::vector<double> inputs{};
  std::vector<Neuron> neurons{};

 /* Constructor
  * @args
  * number_of_neurons: the number of neurons in the layer
  * number_of_inputs:  the number of inputs to be fed into the layer
  *                   i.e. the number of outputs from the preceding layer
  */
  Layer(std::vector<Neuron> new_neurons):neurons{new_neurons}{};
  Layer(){};

  inline void feed(std::vector<double> new_inputs){inputs = new_inputs;}

  // Activates all neurons in the layer
  void forward();

  // Returns the outputs of every neuron in this layer as an stl vector
  std::vector<double> getOutputs();

  // Returns the number of neurons in the layer
  inline unsigned short size() const { return neurons.size();}
};

#endif
