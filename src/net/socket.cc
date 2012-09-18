//
//  Olli's C++ Library
//  net/socket.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/socket.h>

om::net::Socket::Socket(const om::net::IOInterface::iface_type type,
  const om::net::tp_addr addr)
  : om::net::IOInterface(type), _addr(addr) {} 

om::net::Socket::Socket(const om::net::Socket &copy_from)
  : om::net::IOInterface(copy_from), _addr(copy_from._addr) {} 

om::net::Socket& om::net::Socket::operator=(om::net::Socket& copy_from) {

  om::net::IOInterface::operator=(copy_from);
  _addr = copy_from._addr;

  return *this;
}

om::net::tp_addr om::net::Socket::addr() {

  return _addr;
}

om::net::Socket::~Socket() {}
