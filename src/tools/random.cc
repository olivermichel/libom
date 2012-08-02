//
//  Olli's C++ Library
//  tools/random.cc
//  (c) 2012 Oliver Michel
//

#include <om/tools/random.h>

void om::tools::random::seed() {

  srand(time(NULL));
}

double om::tools::random::uniform_sample(double lower, double upper) {

  return (rand()/double(RAND_MAX)*(upper-lower)+lower);
}

double om::tools::random::exponential_sample(double lambda) {

  return (-log(rand()/double(RAND_MAX)))/lambda;
}
    