//
//  Olli's C++ Library
//  net/datagram_socket.cc
//  (c) 2012 Oliver Michel
//

#include <cstring>
#include "datagram_socket.h"

om::net::DatagramSocket::DatagramSocket()
  : om::net::IOInterface() {}

om::net::DatagramSocket::DatagramSocket(const om::net::tp_addr addr) 
  throw(std::runtime_error, std::invalid_argument)
  : om::net::IOInterface() {

  this->open(addr);
}

om::net::DatagramSocket::DatagramSocket(const om::net::DatagramSocket& copy_from)
  : om::net::IOInterface(copy_from) {}

om::net::DatagramSocket& 
  om::net::DatagramSocket::operator=(om::net::DatagramSocket& copy_from) {

  om::net::IOInterface::operator=(copy_from);
  return *this;
}

int om::net::DatagramSocket::open(const om::net::tp_addr addr) 
  throw(std::runtime_error, std::logic_error, std::invalid_argument) {

  if(_fd != 0) 
    throw std::logic_error("Socket already opened");
  
  if(addr.proto != om::net::tp_proto_udp)
    throw std::invalid_argument("ip_endpoint must be an UDP endpoint");

  int fd, yes = 1;
  struct sockaddr_in addr_struct;

  // create new datagram socket
  if((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    throw std::runtime_error("socket(): " + std::string(strerror(errno)));

  // reuse socket address if in use
  if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    throw std::runtime_error("setsockopt(): " + std::string(strerror(errno)));

  // fill sockaddr_in struct
  om::net::sockaddr_from_tp_addr(addr, &addr_struct);

  // bind newly created socket to address
  if(bind(fd, (struct sockaddr*)&addr_struct, sizeof(addr_struct)) == -1)
    throw std::runtime_error("bind(): " + std::string(strerror(errno)));

  _fd = fd;
  _addr = addr;

  return fd;
}

int om::net::DatagramSocket::send(const om::net::tp_addr remote_addr, 
  const unsigned char* tx_data, const size_t data_len) {

  struct sockaddr_in remote_addr_struct;
  om::net::sockaddr_from_tp_addr(remote_addr, &remote_addr_struct);
  
  int tx_bytes = sendto(_fd, tx_data, data_len, 0, 
    (struct sockaddr *)&remote_addr_struct, sizeof(remote_addr_struct));

  return tx_bytes;
}

int om::net::DatagramSocket::receive(om::net::tp_addr* from, 
  unsigned char* rx_buf, const size_t buf_len) {

  struct sockaddr_in rx_addr;
  socklen_t addr_len = sizeof(rx_addr);

  int rx_bytes = recvfrom(_fd, rx_buf, buf_len, 0, (struct sockaddr *)&rx_addr,
    &addr_len);

  if(rx_bytes == -1)
    throw std::runtime_error("recvfrom(): " + std::string(strerror(errno)));

  from->addr = om::net::nw_addr(rx_addr.sin_addr.s_addr);
  from->port = ntohs(rx_addr.sin_port);
  from->proto = om::net::tp_proto_udp;

  return rx_bytes;
}

void om::net::DatagramSocket::close() 
  throw(std::logic_error) {

  if(_fd == 0)
    throw std::logic_error("Socket was not yet opened");

  ::close(_fd);
}

om::net::DatagramSocket::~DatagramSocket() {

  //this->close();
}
