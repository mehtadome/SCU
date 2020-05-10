#include "random.h"
#include <iostream>
#include <cstdio> 

using std::printf;
using namespace coen79_lab2_p2;

namespace coen79_lab2_p2 {

// Create a new random number
int rand_gen::next(){
  // set the new seed automatically
  currentSeed = rand_gen::equation(currentSeed, currMultiplier, currIncrementer, currModulus);
  return currentSeed;
}

// Set a new seed
void rand_gen::set_seed(int newSeed){
  currentSeed = newSeed;
}

void rand_gen::print_info(){
  std::printf("Seed: %d, Multiplier: %d, Incrementer: %d, Modulus: %d\n", 
    currentSeed, currMultiplier, currIncrementer, currModulus);
}

// Provate method for doing the math
int rand_gen::equation(int seed, int multiplier, int incrementer, int modulus){

  int total = (multiplier * seed + incrementer) % modulus;
  return total;
}

} // end of namespace
