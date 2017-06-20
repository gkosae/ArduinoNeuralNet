#include "layer.h"

void Layer::forward() {
  // Activate every neuron in layer
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
