//
//  Olli's C++ Library
//  net/io_interface.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/io_interface.h>

om::net::IOInterface::IOInterface(om::net::IOInterface::iface_type type) 
  : _fd(0), _iface_type(type) {}

om::net::IOInterface::IOInterface(const om::net::IOInterface &copy_from) 
  : _fd(copy_from._fd), _iface_type(copy_from._iface_type) {}

om::net::IOInterface& 
  om::net::IOInterface::operator=(const om::net::IOInterface& copy_from) {

  _fd = copy_from._fd;
  _iface_type = copy_from._iface_type;

  return *this;
}

int om::net::IOInterface::fd() {

  return _fd;
}

void om::net::IOInterface::add_to_fd_set(fd_set *fds)
  throw(std::logic_error) {

  if(_fd == 0)
    throw std::logic_error("add_to_fd_set(): Interface is not opened");

  FD_SET(_fd, fds);
}

void om::net::IOInterface::remove_from_fd_set(fd_set *fds)
  throw(std::logic_error) {

  if(_fd == 0)
    throw std::logic_error("remove_from_fd_set: Interface is not opened");
  
  FD_CLR(_fd, fds);
}

om::net::IOInterface::iface_type om::net::IOInterface::type() {

  return _iface_type;
}
