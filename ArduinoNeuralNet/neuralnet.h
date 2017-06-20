#ifndef H_NEURALNET
#define H_NEURALNET

#include <StandardCplusplus.h>
#include <vector>
#include "layer.h"

using namespace std;

class NeuralNet {
private:
  // vector holding layers of the neural network
  vector<Layer> layers{};

public:
  NeuralNet(){};
  inline void addLayer(Layer new_layer){layers.push_back(new_layer);}
  void forward();
  inline vector<double> getOutputs(){return layers.back().getOutputs();}
  inline void feed(vector<double> inputs){layers.front().inputs = inputs;}
};

#endif
