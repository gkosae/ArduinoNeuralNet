#include <iostream>
#include <random>
#include <vector>

using namespace std;

short randomGenerator(short min, short max) {
  mt19937 rng;
  rng.seed(random_device()());
  uniform_int_distribution<mt19937::result_type>dist(min, max);

  return dist(rng);
}

int main(int argc, char const *argv[]) {

  // srand(time(NULL));
  // double random_number = 0;
  //
  //
  // for (size_t i = 0; i < 10; i++) {
  //   random_number = randomGenerator(0, 100);
  //   cout << random_number << '\n';
  // }

  double d = (-0.12) * 0.249876 * 0;
  cout << d ;
}
