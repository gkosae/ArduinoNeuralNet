#ifndef H_LAYER
#define H_LAYER

#include "neuron.h"
#include <vector>
#include <iostream>

struct Layer {
  std::vector<double> inputs{};
  std::vector<Neuron> neurons{};

 /*
  * Constructor<br/>
  * @args<br/>
  *     number_of_neurons: number of neurons in the layer<br/>
  *     number_of_inputs: number of inputs being fed into the layer
  */
  Layer(unsigned short number_of_neurons, unsigned short number_of_inputs);

  //Sets the inputs going into the layer
  inline void feed(std::vector<double> new_inputs){inputs = new_inputs;}

  // Activates all neurons in the layer
  void forward();

  // Returns the outputs of every neuron in this layer as an stl vector
  std::vector<double> getOutputs();

  // Returns the number of neurons in the layer
  inline unsigned short size() const { return neurons.size();}
};

#endif
