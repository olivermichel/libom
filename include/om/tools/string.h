//
//  Olli's C++ Library
//  tools/string.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_TOOLS_STRING_H
#define OM_TOOLS_STRING_H

#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace om {
  namespace tools {
    namespace string {

      void split(const std::string& s, char c, std::vector<std::string>& v);

    }
  }
}

#endif