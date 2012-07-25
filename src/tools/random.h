//
//  Olli's C++ Library
//  tools/random.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_TOOLS_RANDOM_H
#define OM_TOOLS_RANDOM_H

#include <cmath>

#include <time.h>
#include <stdlib.h>

#include "tools.h"

namespace om {
  namespace tools {
    namespace random {

      void seed();
      double uniform_sample(double lower, double upper);
      double exponential_sample(double lambda);
    }
  }
}

#endif
