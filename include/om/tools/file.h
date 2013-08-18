//
//  Olli's C++ Library
//  (c) 2013 Oliver Michel <oliver.michel@editum.de>
//

#ifndef OM_TOOLS_FILE_H
#define OM_TOOLS_FILE_H

#include <fstream>
#include <stdexcept>
#include <string>
#include <stdint.h>

namespace om {
	namespace tools {
		namespace file {

			template <class T>
			void write_uint_lit(std::string file_name, T data) throw(std::runtime_error);

			template <class T>
			T read_uint_lit(std::string file_name) throw(std::runtime_error);

      template <class T>
      void write_int_lit(std::string file_name, T data) throw(std::runtime_error);

      template <class T>
      T read_int_lit(std::string file_name) throw(std::runtime_error);

		}
	}
}

#endif
