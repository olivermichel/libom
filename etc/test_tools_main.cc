//
//  Olli's C++ Library
//  test_tools_main.cc
//  (c) 2012 Oliver Michel
//

#include <iostream>

#include "tools/tools.h"

#include "tools/random.h"

int main(int argc, char const *argv[]) {

  om::tools::random::seed();


  for(int i = 0; i < 200; i++)
    std::cout << om::tools::random::exponential_sample(1.0) << std::endl;


  return 0;
}
