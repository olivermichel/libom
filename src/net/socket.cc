//
//  Olli's C++ Library
//  net/socket.cc
//  (c) 2012 Oliver Michel
//

#include "socket.h"

om::net::Socket::Socket(const om::net::IOInterface::iface_type type, 
  const om::net::ip_pair ip_pair)
  : om::net::IOInterface(type), _addr(ip_pair.src), 
    _default_remote_addr(ip_pair.dst) {}

om::net::Socket::Socket(const om::net::IOInterface::iface_type type, 
  const om::net::ip_endpoint addr)
  : om::net::IOInterface(type), _addr(addr) {}

om::net::Socket::Socket(const om::net::Socket &copy_from)
  : om::net::IOInterface(copy_from), _addr(copy_from._addr),
    _default_remote_addr(copy_from._default_remote_addr) {} 

om::net::ip_endpoint om::net::Socket::addr() {

  return _addr;
}

om::net::ip_endpoint om::net::Socket::default_remote_addr() {

  return _default_remote_addr;
}

void om::net::Socket::set_default_remote_addr(const om::net::ip_endpoint remote) {

  _default_remote_addr = remote;
}

om::net::Socket::~Socket() { }
