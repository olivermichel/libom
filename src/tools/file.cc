//
//  Olli's C++ Library
//  (c) 2013 Oliver Michel <oliver.michel@editum.de>
//

#include <om/tools/file.h>

template<class T>
void om::tools::file::write_uint_lit(std::string file_name, T data)
	throw(std::runtime_error) {

	std::ofstream file(file_name.c_str(), std::ios::out | std::ios::trunc);

	if(file.good()) {

		file << (sizeof(T) > 1 ? (T) data : (unsigned) data);
		file.close();

	} else throw std::runtime_error("write_uint_lit: failed opening file");
}

template<class T>
T om::tools::file::read_uint_lit(std::string file_name)
	throw(std::runtime_error) {

	T value = 0;
	std::ifstream file(file_name.c_str(), std::ios::in);

	if(file.good()) {
		
		file >> value;

	} else throw std::runtime_error("read_uint_lit: failed opening file");

	file.close();

	return value;
}

template void om::tools::file::write_uint_lit<uint8_t>(std::string file_name, 
	uint8_t data);

template uint8_t om::tools::file::read_uint_lit<uint8_t>(std::string file_name);

template void om::tools::file::write_uint_lit<uint16_t>(std::string file_name, 
	uint16_t data);

template uint16_t om::tools::file::read_uint_lit<uint16_t>(std::string file_name);

template void om::tools::file::write_uint_lit<uint32_t>(std::string file_name, 
	uint32_t data);

template uint32_t om::tools::file::read_uint_lit<uint32_t>(std::string file_name);

template void om::tools::file::write_uint_lit<uint64_t>(std::string file_name, 
	uint64_t data);

template uint64_t om::tools::file::read_uint_lit<uint64_t>(std::string file_name);
