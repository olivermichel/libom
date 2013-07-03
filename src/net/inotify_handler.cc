//
//  Olli's C++ Library
//  net/inotify_handler.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//

#include <om/net/inotify_handler.h>

om::net::INotifyHandler::INotifyHandler()
	throw(std::runtime_error)
	: om::net::IOInterface(om::net::IOInterface::iface_type_inotify_handler) {

	// create new inotify instance
	if((_fd = inotify_init()) < 0)
		throw std::runtime_error("inotify_init(): " + std::string(strerror(errno)));
}

om::net::INotifyHandler::INotifyHandler(const om::net::INotifyHandler& copy_from)
	: om::net::IOInterface(copy_from) {}

om::net::INotifyHandler& 
	om::net::INotifyHandler::operator=(INotifyHandler& copy_from) {

	om::net::IOInterface::operator=(copy_from);
	return *this;
}

void om::net::INotifyHandler::add_watch(std::string pathname, uint32_t mask)
	throw(std::runtime_error) {

	int wd = -1;

	if((wd = inotify_add_watch(_fd, pathname.c_str(), mask)) < 0)
		throw std::runtime_error("inotify_add_watch(): " + std::string(strerror(errno)));

	// TODO: later split up the error types into runtime_error and invalid_argument

	std::cout << "watch added" << std::endl;	
}


ssize_t om::net::INotifyHandler::read_event(char* buf, size_t len)
	throw(std::runtime_error) {

	ssize_t read_len = -1;

	if((read_len = read(_fd, buf, len)) < 0)
		throw std::runtime_error("read(): " + std::string(strerror(errno)));

	return read_len;
}


om::net::INotifyHandler::~INotifyHandler() {}
