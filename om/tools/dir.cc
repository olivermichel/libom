//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  tools/dir.cc
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include "dir.h"

#include <algorithm>
#include <dirent.h>

std::vector<om::tools::dir::entry> om::tools::dir::contents(std::string path) 
	throw(std::runtime_error)
{
	struct dirent* dirent;
	DIR* dir;
	std::vector<om::tools::dir::entry> v;

	if((dir = opendir(path.c_str())) != NULL) {

		while((dirent = readdir(dir)) != NULL)
      	v.push_back({std::string(dirent->d_name), dirent->d_type});

	} else {
		throw std::runtime_error("om::tools::dir::contents: failed opening directory");
	}

	return v;
}


bool om::tools::dir::contains(std::string path, std::string entry)
	throw(std::runtime_error)
{
	for(om::tools::dir::entry e : om::tools::dir::contents(path))
		if(e.name == entry)
			return true;

	return false;
}
