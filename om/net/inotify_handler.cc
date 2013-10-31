//
//  Olli's C++ Library
//  net/inotify_handler.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//

#include "inotify_handler.h"

om::net::INotifyHandler::INotifyHandler()
	throw(std::runtime_error)
	: om::net::IOInterface(om::net::IOInterface::iface_type_inotify_handler),
		_watches(new std::map<int, std::string>()) {

	// create new inotify instance
	if((_fd = inotify_init()) < 0)
		throw std::runtime_error("inotify_init(): " + std::string(strerror(errno)));
}

om::net::INotifyHandler::INotifyHandler(const om::net::INotifyHandler& copy_from)
	: om::net::IOInterface(copy_from), _watches(copy_from._watches) {}

om::net::INotifyHandler& 
	om::net::INotifyHandler::operator=(INotifyHandler& copy_from) {

	om::net::IOInterface::operator=(copy_from);
	_watches = copy_from._watches;

	return *this;
}

int om::net::INotifyHandler::add_watch(std::string pathname, uint32_t mask)
	throw(std::runtime_error, std::logic_error) {

	int wd = -1;

	if((wd = inotify_add_watch(_fd, pathname.c_str(), mask)) < 0) {

		if(errno == ENOMEM || errno == ENOSPC)
			throw std::runtime_error("inotify_add_watch(): " 
				+ std::string(strerror(errno)));
		else
			throw std::logic_error("inotify_add_watch(): " 
				+ std::string(strerror(errno)));
	}

	_watches->insert(std::make_pair(wd, pathname));

	return wd;
}


void om::net::INotifyHandler::remove_watch(int wd)
  throw(std::logic_error) {

  std::map<int, std::string>::iterator i;

  if(_watches->find(wd) != _watches->end()) {

  	if(inotify_rm_watch(_fd, wd) < 0)
  		throw std::logic_error("inotify_rm_watch(): "
  			+ std::string(strerror(errno)));
		
		_watches->erase(i);

  } else {
  	throw std::logic_error("remove_watch(): wd was not registered: " + wd);
  }

}


ssize_t om::net::INotifyHandler::read_event(char* buf, size_t len)
	throw(std::runtime_error) {

	ssize_t read_len = -1;

	if((read_len = read(_fd, buf, len)) < 0)
		throw std::runtime_error("read(): " + std::string(strerror(errno)));

	return read_len;
}

std::string om::net::INotifyHandler::pathname_for_watch(int wd) const
	throw(std::logic_error) {

	std::map<int, std::string>::const_iterator i;

	if((i = _watches->find(wd)) != _watches->end())
		return i->second;
	else
		throw std::logic_error("pathname_for_watch: invalid watch descriptor " + wd);
}

const std::map<int, std::string>* om::net::INotifyHandler::watches() const {

	return _watches;
}

om::net::INotifyHandler::~INotifyHandler() {}
