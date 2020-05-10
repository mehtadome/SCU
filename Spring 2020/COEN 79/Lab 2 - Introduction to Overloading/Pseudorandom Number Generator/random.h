#ifndef RAND_H
#define RAND_H
#include <iostream>

namespace coen79_lab2_p2 {

class rand_gen {
  public:

    // constructor
    rand_gen (int seed=0, int multiplier=0, int incrementer=0, int modulus=0){
      currentSeed = seed;
      currMultiplier = multiplier;
      currIncrementer = incrementer;
      currModulus = modulus;
    }

    int next();
    void set_seed(int newSeed);
    void print_info();

  private:
    // store original seed value per calculation
    int currentSeed;
    int currMultiplier;
    int currIncrementer;
    int currModulus;

    int equation(int seed, int multiplier, int incrementer, int modulus);

};

} // end of namespace
#endif

