//
//  Olli's C++ Library
//  net/stream_client.cc
//  (c) 2013 Oliver Michel
//

#include <om/net/stream_client.h>

om::net::StreamClient::StreamClient(const om::net::tp_addr addr,
  const om::net::tp_addr server_addr) 
  throw(std::runtime_error, std::invalid_argument)
  : om::net::Socket(om::net::IOInterface::iface_type_sock_stream, addr),
    _server_addr(server_addr) {

  this->open(server_addr);
}

om::net::StreamClient::StreamClient(const om::net::StreamClient &copy_from)
  : om::net::Socket(copy_from), _server_addr(copy_from._server_addr) {}

om::net::StreamClient& om::net::StreamClient::operator=(StreamClient& copy_from) {

  om::net::Socket::operator=(copy_from);
  _server_addr = copy_from._server_addr;

  return *this;
}

int om::net::StreamClient::open(const om::net::tp_addr server_addr)
  throw(std::runtime_error, std::logic_error, std::invalid_argument) {

  return 0;
}

void close()
  throw(std::logic_error) {

}
      
om::net::StreamClient::~StreamClient() {}
