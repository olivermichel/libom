//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_connection.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//

#include <om/net/stream_connection.h>

om::net::StreamConnection::StreamConnection()
  : om::net::Socket(om::net::IOInterface::iface_type_sock_stream) {}

om::net::StreamConnection::StreamConnection(const om::net::StreamConnection &copy_from)
  : om::net::Socket(copy_from), _remote_addr(copy_from._remote_addr) {}

om::net::StreamConnection& om::net::StreamConnection::operator=(StreamConnection& copy_from) {

  om::net::Socket::operator=(copy_from);
  _remote_addr = copy_from._remote_addr;
  return *this;
}

om::net::StreamConnection::~StreamConnection() {}
