
#include "multiplex_interface.h"

om::async::MultiplexInterface::MultiplexInterface()
	: _fd(0) {}

om::async::MultiplexInterface::MultiplexInterface(int fd)
	: _fd(fd) {}

int om::async::MultiplexInterface::fd()
{
	return _fd;
}

void om::async::MultiplexInterface::set_fd(int fd)
{
	_fd = fd;
}

om::async::MultiplexInterface::~MultiplexInterface() {}