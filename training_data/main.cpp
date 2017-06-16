#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

double stringToDouble(string);
void processFile(string);
void shuffleValues(vector<double> &);
double randomize();
int randomize(int);

int main(int argc, char* argv[]) {
    string filename = argv[1];
    processFile(filename);
    return 0;
}

void processFile(string infile) {

    ifstream ifs{infile};

    string outfile = infile + ".processed";
    ofstream ofs{outfile};


    string buffer{};
    vector<double> values{};

    while(ifs >> buffer)
        values.push_back(stringToDouble(buffer));

    cout << "Shuffling values....." << endl;
    shuffleValues(values);

    for(auto& value : values) {
      ofs << value << endl;
    }
}

double stringToDouble(string str) {
    stringstream ss{str};
    double val;
    ss >> val;
    return val;
}

void shuffleValues(vector<double>& values) {
    unsigned short size = values.size();
    unsigned short shuffle_times = 10; //number of times to shuffle
    double swap_probability = 0;
    int swap_position = 0;

    for(auto i = 0; i <  shuffle_times; ++i) {
        for(auto j = 1; j < size; ++j) {
          swap_probability = randomize();

          if(swap_probability > 0.5){
	      
	      swap_position = randomize(size - 1);
	      if(j == swap_position)continue;

              swap(values.at(j), values.at(swap_position));
              cout << "Swapping values at " << j << " and " << swap_position << endl;
          }
        }
    }
}

double randomize() {
  short min = 0;
  short max = 100;

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type>dist(min, max);
  double random_number = (double)dist(rng)/(double)max;
  return random_number;
}

int randomize(int max) {
  unsigned short min = 1;
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type>dist(min, max);
  return dist(rng);
}
