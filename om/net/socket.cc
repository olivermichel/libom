//
//  Olli's C++ Library
//  net/socket.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//

#include "socket.h"

om::net::Socket::Socket(const om::net::IOInterface::iface_type type)
	: om::net::IOInterface(type) {}

om::net::Socket::Socket(const om::net::Socket &copy_from)
	: om::net::IOInterface(copy_from) {}

om::net::Socket& om::net::Socket::operator=(om::net::Socket& copy_from) {

	om::net::IOInterface::operator=(copy_from);
	return *this;
}

om::net::Socket::~Socket() {}
