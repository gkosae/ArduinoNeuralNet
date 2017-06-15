#ifndef H_NEURALNET
#define H_NEURALNET

#define VERBOSE

#include <vector>
#include <sstream>
#include <fstream>
#include "layer.h"

using namespace std;

class NeuralNet {
private:
  // Network Hyperparameters

  // Minimum error that must be reached before training stops
  double minimum_error = 1e-8;

  // User defined learning rate used for updating network weights (default 3)
  double learning_rate = 3;

  // Max number of epochs before the training stops (default 50000)
  long max_iteration_number;

  // vector holding layers of the neural network
  vector<Layer> layers{};

  // Actual output for current samples
  vector<vector<double>> actual_output{};

  // The user-defined expected output pattern for a set of samples
  vector<vector<double>> expected_output{};

  //The user-defined input pattern for a set of samples
  vector<vector<double>> input_data{};

  unsigned int current_sample = 0;

  // Regularization Hyperparameter
  double lambda = 1;

  // Normalizing parameters
  // double input_normalizer = 1;
  // double output_normalizer = 1;


  // helper functions
  void updateWeights();
  void backpropagateErrors();
  void adjustWeights();
  double calculateOverallError();
  std::string buildInfoString();
  void getNetworkInfo(stringstream& ss);
  void getLayerInfo(stringstream& ss);
  void getNeuronInfo(stringstream& ss);
  std::string buildCodeString();
  void includeHeaders(stringstream& ss);
  void writeBody(stringstream& ss);
  double getRegularizationTerm();

public:
  NeuralNet(){};
  inline void addLayer(Layer new_layer){layers.push_back(new_layer);}
  void train(vector<vector<double>> input_samples,
                    vector<vector<double>> output_samples,
                    double learn_rate = 3,
                    double new_lambda = 1e-12,
                    long max_iter = 50000);

  void forward();
  inline vector<double> getOutputs(){return layers.back().getOutputs();}
  inline void feed(vector<double> inputs){layers.front().inputs = inputs;}
  void printNetworkInfo(std::string file = "neuralnet.info");
  void generateArduinoCode(std::string file = "neuralnet.code");
};

#endif
