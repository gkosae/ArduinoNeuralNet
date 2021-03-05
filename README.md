# ArduinoNeuralNet
This is just a little something I created for my undergraduate
final year project. It is a neural network library used for supervised 
learning. It uses backpropagation with gradient descent for learning 
and handles overfitting to some degree with L2 regularization.

This project is made up of two parts.

## ArduinoNeuralNet (A minimized neural network library)
This is everything found in the ArduinoNeuralNet folder.
It is meant be used on the arduino platform.
Refer to [this guide](https://www.arduino.cc/en/guide/libraries) for installation instructions.

## The rest
This is anything else not found in the ArduinoNeuralNet folder.
With this, you can create and train a multilayered feed-forward neural network.
For my convenience, it is able to generate arduino code 
containing the structure and content (weights and biases) of the 
network after training for use in arduino projects. Its been tried and tested on 
Linux (Ubuntu).

ArduinoNeuralNet depends on the awesome library, [StandardCplusplus](https://github.com/maniacbug/StandardCplusplus), by 
maniacbug. Install it alongside. 

There is only one example at the moment, i.e. in main.cpp. But I'll 
add more really soon. :)

## Build
To build this, run 
```
make
``` 
in the root folder. It uses clang to build by default. But you can change this to another compiler by using the CXX option. E.g. to use g++ run
```
make CXX=g++
```

Use
```
make run
```
To try out the example that comes with this
