#include "neuralnet.h"
#include <iostream>
#include <cmath>

void NeuralNet::train(vector<vector<double>> input_samples,
                             vector<vector<double>> output_samples,
                             double learn_rate,
                             double new_lambda,
                             long max_iter)
{
    input_data = input_samples;
    expected_output = output_samples;
    actual_output = std::vector<vector<double>>(input_data.size());

    lambda = new_lambda;
    learning_rate = learn_rate;
    max_iteration_number = max_iter;

    double overall_error = 0;
    unsigned int number_of_samples = input_data.size();
    unsigned int iteration_number = 0;

    do
    {
        for(current_sample = 0; current_sample <  number_of_samples; ++current_sample) {
          feed(input_data.at(current_sample));
          forward();

          actual_output.at(current_sample) = getOutputs();
          updateWeights();
        }

        overall_error = calculateOverallError();
        ++iteration_number;

        #ifdef VERBOSE
            std::cout << "Current error = " << overall_error << "\n";
        #endif
    } while (overall_error > minimum_error && iteration_number < max_iteration_number);

    #ifdef VERBOSE
    std::cout << "\nTRAINING RESULTS" << "\n"
              << "Overall error: " << overall_error << "\n"
              << "Total number of iterations: " << iteration_number << "\n\n";
    #endif

}

void NeuralNet::forward() {
    // set inputs as output of the input layer
    unsigned short input_layer_size = layers.front().size();

    for(auto i = 0; i < input_layer_size; ++i) {
      layers.front().neurons.at(i).output = layers.front().inputs.at(i);
    }

     layers.at(1).feed(layers.front().getOutputs());

     unsigned short number_of_layers = layers.size();

     for(auto i = 1; i < number_of_layers; ++i) {
        layers.at(i).forward();

        if(i != (number_of_layers - 1)){
            layers.at(i+1).feed(layers.at(i).getOutputs());
        }
     }
}

void NeuralNet::updateWeights() {
    backpropagateErrors();
    adjustWeights();
}

void NeuralNet::backpropagateErrors() {
    // Calculate delta (backpropagating error) for output layer
    unsigned short output_layer_size = layers.back().size();

    for(auto i = 0; i < output_layer_size; ++i) {

        layers.back().neurons.at(i).delta = (actual_output.at(current_sample).at(i) -
                                             expected_output.at(current_sample).at(i)) *
                                             layers.back().neurons.at(i).sigmoidPrime();
    }

    unsigned short number_of_hidden_layers = layers.size() - 2;

    for(auto i = number_of_hidden_layers; i > 0 ; --i) {

      unsigned short current_layer_size = layers.at(i).size();
      unsigned short next_layer_size = layers.at(i+1).size();

      for(auto j = 0; j < current_layer_size; ++j) {

          double delta = 0;
          for(auto k = 0; k <  next_layer_size; k++) {
              delta += (layers.at(i+1).neurons.at(k).delta *
                        layers.at(i+1).neurons.at(k).weights.at(j) *
                        layers.at(i).neurons.at(j).sigmoidPrime());
          }

          layers.at(i).neurons.at(j).delta = delta;
      }
    }
}

void NeuralNet::adjustWeights() {
    unsigned short count = layers.size();

    for(auto i = 1; i < count; ++i) {
        unsigned short current_layer_size = layers.at(i).size();

        for(auto j = 0; j <  current_layer_size; ++j) {
            unsigned short number_of_weights = layers.at(i).neurons.at(j).getNumberOfWeights();
            double delta = layers.at(i).neurons.at(j).delta;

            for(auto k = 0; k < number_of_weights; ++k) {
                double old_weight = layers.at(i).neurons.at(j).weights.at(k);
                double change_in_weight = (delta * layers.at(i).inputs.at(k)) + lambda*old_weight;
                double new_weight = old_weight - change_in_weight*learning_rate;
                layers.at(i).neurons.at(j).weights.at(k) = new_weight;
            }

            double old_threshold = layers.at(i).neurons.at(j).threshold;
            double change_in_threshold = delta * layers.at(i).neurons.at(j).bias;
            double new_threshold = old_threshold - change_in_threshold*learning_rate;
            layers.at(i).neurons.at(j).threshold = new_threshold;
        }
    }
}

double NeuralNet::calculateOverallError() {
    double error = 0;

    // Quadratic Cost Function
    for(auto i = 0; i < current_sample; ++i) {
        unsigned short output_layer_size = layers.back().size();
        for(auto j = 0; j < output_layer_size; ++j) {
            error += (0.5*pow(expected_output[i][j] - actual_output[i][j], 2));
        }
    }

    unsigned short number_of_samples = input_data.size();

    error = error/number_of_samples + lambda/2*getRegularizationTerm();
    return error;
}


double NeuralNet::getRegularizationTerm() {
    double term = 0;

    // sum the square of all weights
    unsigned short count = layers.size();

    for(auto i = 1; i < count; ++i) {
        unsigned short current_layer_size = layers.at(i).size();

        for(auto j = 0; j < current_layer_size; ++j) {
            std::vector<double> weights = layers.at(i).neurons.at(j).weights;

            for(auto weight : weights) {
                term += pow(weight,2);
            }
        }
    }

    term = term/input_data.size();
    return term;
}

void NeuralNet::printNetworkInfo(std::string file) {
  ofstream ofs{file};
  string info_string = buildInfoString();
  ofs << info_string;
}

std::string NeuralNet::buildInfoString() {
  stringstream ss{};
  getNetworkInfo(ss);
  getLayerInfo(ss);
  getNeuronInfo(ss);
  return ss.str();
}

void NeuralNet::getNetworkInfo(stringstream& ss) {
  ss << "NETWORK INFO\n";
  ss << "Number of inputs: " << layers.front().size() << '\n';
  ss << "Number of outputs: " << layers.back().size() << '\n';
  ss << "Number of hidden layers: " << layers.size() - 2 << '\n';
  ss << '\n';
}

void NeuralNet::getLayerInfo(stringstream& ss) {
  if((layers.size() - 2) == 0 ) return;

  ss << "LAYER INFO\n";

  // Print info on the hidden layers
  unsigned short number_of_hidden_layers = layers.size() - 2;

  for(auto i = 1; i <= number_of_hidden_layers; i++) {
    ss << "Size of hidden layer " << i << ": " << layers.at(i).size() << '\n';
  }

  ss << '\n';
}

void NeuralNet::getNeuronInfo(stringstream &ss) {
  ss << "DETAILED INFO\n";

  // print detailed info of all layers starting from the first hidden layer
  unsigned short count  = layers.size();

  for(auto i = 1; i < count; i++) {

    if(i == count - 1) ss << "Output Layer\n";
    else
        ss << "Hidden Layer " << i << '\n';

    unsigned short current_layer_size = layers.at(i).size();
    for(auto j = 0; j < current_layer_size; j++) {
      ss << "Neuron " << j+1 << ": weights ( ";

      for(auto weight : layers.at(i).neurons.at(j).weights) {
        ss << weight << " ";
      }

      ss << ") , threshold ( " << layers.at(i).neurons.at(j).threshold << " )\n";
    }

    ss << '\n';
  }
}

void NeuralNet::generateArduinoCode(std::string file) {
    ofstream ofs{file};
    std::string code_string = buildCodeString();
    ofs << code_string;
}

std::string NeuralNet::buildCodeString() {
    stringstream ss{};
    includeHeaders(ss);
    writeBody(ss);
    return ss.str();
}

void NeuralNet::includeHeaders(stringstream& ss) {
    ss << "#include <StandardCplusplus.h>\n";
    ss << "#include <system_configuration.h>\n";
    ss << "#include \"neuralnet.h\"\n\n";
    ss << "using namespace std;\n\n";
}

void NeuralNet::writeBody(stringstream& ss) {
    ss << "NeuralNet network{};\n\n";

    ss << "// Function to populate neural network\n";
    ss << "void populateNetwork() {\n";
    ss << "\tvector<Neuron> temp{};\n\n";

    std::string input_neuron_prefix = "in_";
    std::string output_neuron_prefix = "out_";
    std::string hidden_layer_prefix = "hi_";

    ss << "\t// Input layer\n";
    unsigned short number_of_inputs = layers.front().size();
    for(auto i = 0; i < number_of_inputs; i++) {
      ss << "\tNeuron " << input_neuron_prefix << i+1 << "{};";
      ss << "\ttemp.push_back(" << input_neuron_prefix << i+1 << ");\n";
    }

    ss << "\tLayer input_layer{temp};\n";
    ss << "\tnetwork.addLayer(input_layer);\n";
    ss << "\ttemp.clear();\n\n";

    // Create hidden layers
    unsigned short number_of_hidden_layers = layers.size() - 2;
    for(auto i = 0; i < number_of_hidden_layers; i++) {

        ss << "\t// Hidden layer " << i+1 << '\n';
        unsigned int current_layer_size = layers.at(i+1).size();
        for(auto j = 0; j < current_layer_size; j++) {
            ss << "\tNeuron " << hidden_layer_prefix << i+1 << "_" << j+1 << "{vector<double>{";
            unsigned short number_of_weights = layers.at(i+1).neurons.at(j).weights.size();

            for(auto k = 0; k <  number_of_weights; k++) {
              ss << layers.at(i+1).neurons.at(j).weights.at(k);
              if(k != number_of_weights - 1) ss << ", ";
            }

            ss << "}, " << layers.at(i+1).neurons.at(j).threshold << "};";
            ss << "\ttemp.push_back(" << hidden_layer_prefix << i+1 << "_" << j+1 << ");\n";
        }

        ss << "\tLayer " << hidden_layer_prefix << i+1 << "{temp};\n";
        ss << "\tnetwork.addLayer(" << hidden_layer_prefix << i+1 << ");\n";
        ss << "\ttemp.clear();\n\n";
    }


    ss << "\t// Output layer\n";
    unsigned short number_of_outputs = layers.back().size();
    for(auto i = 0; i < number_of_outputs; i++) {
      ss << "\tNeuron " << output_neuron_prefix << i+1 << "{vector<double>{";

      unsigned short number_of_weights = layers.back().neurons.at(i).weights.size();

      for(auto j = 0; j < number_of_weights; j++) {
        ss << layers.back().neurons.at(i).weights.at(j);
        if(j != number_of_weights - 1)ss << ", ";
      }

      ss << "}, " << layers.back().neurons.at(i).threshold << "};";
      ss << "\ttemp.push_back(" << output_neuron_prefix << i+1 << ");\n";
    }

    ss << "\tLayer output_layer{temp};\n";
    ss << "\tnetwork.addLayer(output_layer);\n";
    ss << "\ttemp.clear();\n\n";

    ss << "}\n\n";

    ss << "// Arduino boilerplate\n";
    ss << "void setup() {\n";
    ss << "\t populateNetwork();\n";
    ss << "}\n\n";
    ss << "void loop() {\n \n}\n\n";
}
