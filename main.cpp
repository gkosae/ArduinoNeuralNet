#include "neuralnet.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<double>> createInputSamples();
vector<vector<double>> createOutputSamples();
void testNetwork(NeuralNet&);
void printResults(NeuralNet&, vector<double>&);

int number_of_samples = 0;
const int NORMALIZER = 100.00;

int main(int argc, char* argv[]) {
    Layer input_layer{10, 10};
    Layer hidden_layer{2, 10};
    Layer output_layer{2, 2};

    NeuralNet network{};
    network.addLayer(input_layer);
    network.addLayer(hidden_layer);
    network.addLayer(output_layer);

    network.train(createInputSamples(), createOutputSamples());
    network.printNetworkInfo();
    network.generateArduinoCode();
    testNetwork(network);
}

vector<vector<double>> createInputSamples() {

  vector<vector<double>> samples{};
  vector<double> buffer{};
  double temp = 0;

  ifstream ifs{input_data_file};

  while(ifs >> temp) {

      buffer.clear();
      buffer.push_back(temp/NORMALIZER);

      for(auto i = 0; i < 9; ++i) {
        ifs >> temp;
        buffer.push_back(temp/NORMALIZER);
      }
   samples.push_back(buffer);
 }

  number_of_samples = samples.size();
  return samples;
}

vector<vector<double>> createOutputSamples() {

  vector<vector<double>> samples{};

  for(auto i = 0; i < number_of_samples; ++i) {
    samples.push_back(vector<double>{18.00/NORMALIZER, 50.00/NORMALIZER});
  }

  return samples;
}

void testNetwork(NeuralNet& network) {

    vector<double> input_one{25.04, 25, 25, 25, 25, 30, 22, 31, 25, 28};
    vector<double> input_two{34, 31, 26, 22, 21, 35, 22, 31, 25, 18};
    vector<double> input_three{22.04, 35, 29.55, 23, 26, 31, 33, 21, 22, 41};
    vector<double> input_four{50, 50, 50, 50, 50, 50, 50, 50, 50, 50};

    printResults(network, input_one);
    printResults(network, input_two);
    printResults(network, input_three);
    printResults(network, input_four);
}

void printResults(NeuralNet& network, vector<double>& inputs) {

    cout << "Inputs: ";
    for(auto& input : inputs) {
      cout << input << " ";
      input = input/NORMALIZER;
    }

    cout << endl;

    network.feed(inputs);
    network.forward();
    vector<double> outputs = network.getOutputs();

    cout << "Outputs: ";
    for(auto& output : outputs) {
      output = output * NORMALIZER;
      cout << output << " ";
    }

    cout << endl << endl;
}
