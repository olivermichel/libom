//
//  Olli's C++ Library
//  net/datagram_socket.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/datagram_socket.h>

om::net::DatagramSocket::DatagramSocket(const om::net::ip_pair addr_pair)
  throw(std::runtime_error, std::invalid_argument)
  : om::net::Socket(om::net::IOInterface::iface_type_sock_dgram, addr_pair) {

  this->open(addr_pair.src);
}

om::net::DatagramSocket::DatagramSocket(const om::net::ip_endpoint addr) 
  throw(std::runtime_error, std::invalid_argument)
  : om::net::Socket(om::net::IOInterface::iface_type_sock_dgram, addr) {

  this->open(addr);
}

om::net::DatagramSocket::DatagramSocket(const om::net::DatagramSocket &copy_from)
  : om::net::Socket(copy_from) {}

int om::net::DatagramSocket::open(const om::net::ip_endpoint addr) 
  throw(std::runtime_error, std::logic_error, std::invalid_argument) {

  if(_fd != 0) 
    throw std::logic_error("Socket already opened");
  
  if(addr.tp_proto != om::net::tp_proto_udp)
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
  om::net::setup_addr_struct(&addr_struct, AF_INET, addr.nw_addr, addr.tp_addr);

  // bind newly created socket to address
  if(bind(fd, (struct sockaddr *)&addr_struct, sizeof(addr_struct)) == -1)
    throw std::runtime_error("bind(): " + std::string(strerror(errno)));

  _fd = fd, _addr = addr;

  return fd;
}

int om::net::DatagramSocket::send(const unsigned char *tx_data, 
  const size_t data_len) {

  struct sockaddr_in remote_addr_struct;
  om::net::setup_addr_struct(&remote_addr_struct, _default_remote_addr);

  int tx_bytes = sendto(_fd, tx_data, data_len, 0, 
    (struct sockaddr *)&remote_addr_struct, sizeof(remote_addr_struct));

  return tx_bytes;
}

int om::net::DatagramSocket::send(const om::net::ip_endpoint remote_addr, 
  const unsigned char *tx_data, const size_t data_len) {

  struct sockaddr_in remote_addr_struct;
  om::net::setup_addr_struct(&remote_addr_struct, remote_addr);
  
  int tx_bytes = sendto(_fd, tx_data, data_len, 0, 
    (struct sockaddr *)&remote_addr_struct, sizeof(remote_addr_struct));

  return tx_bytes;
}

int om::net::DatagramSocket::receive(om::net::ip_endpoint *from, 
  unsigned char *rx_buf, const size_t buf_len) {

  struct sockaddr_in rx_addr;
  socklen_t addr_len = sizeof(rx_addr);

  int rx_bytes = recvfrom(_fd, rx_buf, buf_len, 0, (struct sockaddr *)&rx_addr,
    &addr_len);

  if(rx_bytes == -1)
    throw std::runtime_error("recvfrom(): " + std::string(strerror(errno)));

  om::net::ip_endpoint_from_addr_struct(&rx_addr, from);
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
