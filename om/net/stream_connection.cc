//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_connection.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include <cstring>
#include <errno.h>
#include <unistd.h>

#include "stream_connection.h"

om::net::StreamConnection::StreamConnection()
	: om::net::Socket(om::net::IOInterface::iface_type_sock_stream) {}

om::net::StreamConnection::StreamConnection(int fd)
	throw(std::logic_error, std::invalid_argument)
	: om::net::Socket(om::net::IOInterface::iface_type_sock_stream) {

	this->attach(fd);
}

om::net::StreamConnection::StreamConnection(int fd, om::net::tp_addr remote_addr)
	throw(std::logic_error, std::invalid_argument)
	: om::net::Socket(om::net::IOInterface::iface_type_sock_stream) {

	this->attach(fd, remote_addr);
}

om::net::StreamConnection::StreamConnection(const om::net::StreamConnection 
	&copy_from)
	: om::net::Socket(copy_from), _remote_addr(copy_from._remote_addr) {}

om::net::StreamConnection& om::net::StreamConnection::operator=(
	StreamConnection& copy_from) {

	om::net::Socket::operator=(copy_from);
	_remote_addr = copy_from._remote_addr;
	return *this;
}

om::net::tp_addr om::net::StreamConnection::remote_addr() {

	return _remote_addr;
}

void om::net::StreamConnection::attach(int fd)
	throw(std::logic_error, std::invalid_argument) {

	if(_fd != 0)
		throw std::logic_error("StreamConnection is already attached to a socket");

	if(fd < 0)
		throw std::invalid_argument("Invalid file descriptor");

	_fd = fd;
}

void om::net::StreamConnection::attach(int fd, om::net::tp_addr remote_addr)
	throw(std::logic_error, std::invalid_argument) {

	_remote_addr = remote_addr;
	this->attach(fd);
}

int om::net::StreamConnection::send(const unsigned char* tx_buf,
	const size_t buf_len) {

	int tx_bytes = ::send(_fd, tx_buf, buf_len, 0);
	return tx_bytes;
}

int om::net::StreamConnection::receive(unsigned char* rx_buf,
	const size_t buf_len) {

	int rx_bytes = ::recv(_fd, rx_buf, buf_len, 0);
	return rx_bytes;
}

void om::net::StreamConnection::close()
	throw(std::logic_error, std::runtime_error) {

	if(_fd == 0)
		throw std::logic_error("Socket was already closed or never opened");

	if(::close(_fd) == 0)
		_fd = 0;
	else
		throw std::runtime_error("close(): " + std::string(strerror(errno)));
}

om::net::StreamConnection::~StreamConnection() {}
