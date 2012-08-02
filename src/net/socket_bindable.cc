//
//  Olli's C++ Library
//  net/socket_bindable.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/socket_bindable.h>

om::net::SocketBindable::SocketBindable()
  : om::net::IOInterface(IOInterface::iface_type_unknown) {}

void om::net::SocketBindable::bind_to_iface(std::string iface) 
  throw(std::runtime_error) {

  struct ifreq ifr;

  memset(&ifr, 0, sizeof(ifr));
  snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), iface.c_str());

  if(setsockopt(_fd, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) == -1)
    throw std::runtime_error("setsockopt(): " + std::string(strerror(errno)));

  _bound_iface = iface;
}
