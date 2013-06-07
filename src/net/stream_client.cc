//
//  Olli's C++ Library
//  net/stream_client.cc
//  (c) 2013 Oliver Michel
//

#include <om/net/stream_client.h>


om::net::StreamClient::StreamClient()
  : om::net::IOInterface(om::net::IOInterface::iface_type_sock_stream) { }

om::net::StreamClient::StreamClient(const om::net::tp_addr remote_addr) 
  throw(std::runtime_error, std::invalid_argument)
  : om::net::IOInterface(om::net::IOInterface::iface_type_sock_stream) {

  this->open(remote_addr);
}

om::net::StreamClient::StreamClient(const om::net::StreamClient& copy_from)
  : om::net::IOInterface(copy_from), _remote_addr(copy_from._remote_addr) {}

om::net::StreamClient& om::net::StreamClient::operator=(StreamClient& copy_from) {

  om::net::IOInterface::operator=(copy_from);
  _remote_addr = copy_from._remote_addr;
  return *this;
}

int om::net::StreamClient::open(const om::net::tp_addr remote_addr)
  throw(std::runtime_error, std::logic_error, std::invalid_argument) {

  int fd;
  struct sockaddr_in remote_addr_struct;
  
  if(_fd != 0) 
    throw std::logic_error("Socket already opened");
  
  if(remote_addr.proto != om::net::tp_proto_tcp)
    throw std::invalid_argument("ip_endpoint must be an UDP endpoint");

  _remote_addr = remote_addr;

  om::net::sockaddr_from_tp_addr(remote_addr, &remote_addr_struct);

  // create new stream socket
  if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw std::runtime_error("socket(): " + std::string(strerror(errno)));

  // connect to server
  if(connect(fd, (struct sockaddr*)&remote_addr_struct, 
    sizeof(remote_addr_struct)) != 0)
    throw std::runtime_error("connect(): " + std::string(strerror(errno)));

  _fd = fd;
  return fd;
}


int om::net::StreamClient::send(const unsigned char* tx_buf, 
  const size_t buf_len) {

  int tx_bytes = ::send(_fd, tx_buf, buf_len, 0);
  return tx_bytes;
}

int om::net::StreamClient::receive(unsigned char* rx_buf, const size_t buf_len) {

  int rx_bytes = recv(_fd, rx_buf, buf_len, 0);
  return rx_bytes;
}

void om::net::StreamClient::close()
  throw(std::logic_error, std::runtime_error) {

  if(_fd == 0)
    throw std::logic_error("Socket was already closed or never opened");

  if(::close(_fd) == 0)
    _fd = 0;
  else
    throw std::runtime_error("close(): " + std::string(strerror(errno)));
}
      
om::net::StreamClient::~StreamClient() { }
