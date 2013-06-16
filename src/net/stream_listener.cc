//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_listener.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//

#include <om/net/stream_listener.h>

om::net::StreamListener::StreamListener()
	: om::net::Socket(om::net::IOInterface::iface_type_sock_stream) {}

om::net::StreamListener::StreamListener(const om::net::tp_addr addr,
	om::net::Agent* conn_handler)
	throw(std::runtime_error, std::invalid_argument)
	: om::net::Socket(om::net::IOInterface::iface_type_sock_stream) {

	this->open(addr, conn_handler);
}

om::net::StreamListener::StreamListener(const om::net::StreamListener &copy_from)
	: om::net::Socket(copy_from), _addr(copy_from._addr), 
		_conn_handler(copy_from._conn_handler) {}

om::net::StreamListener& om::net::StreamListener::operator=(StreamListener& copy_from) {

	om::net::Socket::operator=(copy_from);
	_addr = copy_from._addr;
	_conn_handler = copy_from._conn_handler;
	return *this;
}

int om::net::StreamListener::open(const om::net::tp_addr remote_addr,
	om::net::Agent* conn_handler)
	throw(std::runtime_error, std::logic_error, std::invalid_argument) {

	//TODO: to be implemented
	return 0;
}

void om::net::StreamListener::close()
	throw(std::logic_error, std::runtime_error) {
	
	if(_fd == 0)
		throw std::logic_error("Socket was already closed or never opened");

	if(::close(_fd) == 0)
		_fd = 0;
	else
		throw std::runtime_error("close(): " + std::string(strerror(errno)));
}

om::net::StreamListener::~StreamListener() {}
