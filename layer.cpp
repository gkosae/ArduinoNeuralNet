#include "layer.h"

Layer::Layer(unsigned short number_of_neurons, unsigned short number_of_inputs) {

  neurons = std::vector<Neuron>(number_of_neurons);
  inputs = std::vector<double>(number_of_inputs);

  for (Neuron& neuron : neurons) {
      neuron.reshape(number_of_inputs);
  }
}

void Layer::forward() {
  for (Neuron& neuron : neurons) {
      neuron.activate(inputs);
  }
}

std::vector<double> Layer::getOutputs() {
    std::vector<double> outputs{};
    for (Neuron& neuron : neurons){
        outputs.push_back(neuron.output);
    }

    return outputs;
}
