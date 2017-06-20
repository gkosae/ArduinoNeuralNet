#include "neuralnet.h"

void NeuralNet::forward() {
    // set inputs as output of the input layer
    unsigned short input_layer_size = layers.front().size();

    for(auto i = 0; i < input_layer_size; i++) {
      layers.front().neurons.at(i).output = layers.front().inputs.at(i);
    }

     layers.at(1).feed(layers.front().getOutputs());

     unsigned short number_of_layers = layers.size();

     for(auto i = 1; i < number_of_layers; i++) {
        layers.at(i).forward();

        if(i != (number_of_layers - 1)){
            layers.at(i+1).feed(layers.at(i).getOutputs());
        }
    }
}
