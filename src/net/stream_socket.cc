//
//  Olli's C++ Library
//  net/stream_socket.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/stream_socket.h>

om::net::StreamSocket::StreamSocket(const om::net::tp_addr addr,
  const std::string iface) 
  throw(std::runtime_error, std::invalid_argument)
  : om::net::Socket(om::net::IOInterface::iface_type_sock_stream, addr) {

  this->open(addr, iface);
}

om::net::StreamSocket::StreamSocket(const om::net::StreamSocket& copy_from)
  : om::net::Socket(copy_from) {}

om::net::StreamSocket& 
  om::net::StreamSocket::operator=(om::net::StreamSocket& copy_from) {

  om::net::Socket::operator=(copy_from);
  return *this;
}

int om::net::StreamSocket::open(const om::net::tp_addr addr) 
  throw(std::runtime_error, std::logic_error, std::invalid_argument) {

  return this->open(addr, "");
}


int om::net::StreamSocket::open(const om::net::tp_addr addr, 
  const std::string iface) 
  throw(std::runtime_error, std::logic_error, std::invalid_argument) {

  if(_fd != 0) 
    throw std::logic_error("Socket already opened");
  
  if(addr.proto != om::net::tp_proto_tcp)
    throw std::invalid_argument("ip_endpoint must be a TCP endpoint");

  int fd, yes = 1;
  struct sockaddr_in addr_struct;

  // create new datagram socket
  if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    throw std::runtime_error("socket(): " + std::string(strerror(errno)));

  // reuse socket address if in use
  if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    throw std::runtime_error("setsockopt(): " + std::string(strerror(errno)));

  // fill sockaddr_in struct
  inet_pton(AF_INET, addr.addr.to_cstring(), &addr_struct.sin_addr);
  addr_struct.sin_port = htons(addr.port);
  addr_struct.sin_family = AF_INET;
  std::memset(addr_struct.sin_zero, '\0', sizeof(addr_struct.sin_zero));

  // bind newly created socket to address
  if(bind(fd, (struct sockaddr*)&addr_struct, sizeof(addr_struct)) == -1)
    throw std::runtime_error("bind(): " + std::string(strerror(errno)));

  _fd = fd;
  _addr = addr;

  return fd;
}

int om::net::StreamSocket::send(const om::net::tp_addr remote_addr, 
  const unsigned char* tx_data, const size_t data_len) {

  struct sockaddr_in remote_addr_struct;
  
  // fill sockaddr_in struct
  remote_addr_struct.sin_addr.s_addr = remote_addr.addr.packed();
  remote_addr_struct.sin_port = htons(remote_addr.port);
  remote_addr_struct.sin_family = AF_INET;
  std::memset(remote_addr_struct.sin_zero, '\0', 
    sizeof(remote_addr_struct.sin_zero));
   
  int tx_bytes = sendto(_fd, tx_data, data_len, 0, 
    (struct sockaddr *)&remote_addr_struct, sizeof(remote_addr_struct));

  return tx_bytes;
}

int om::net::StreamSocket::receive(om::net::tp_addr* from, 
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

void om::net::StreamSocket::close() 
  throw(std::logic_error) {

  if(_fd == 0)
    throw std::logic_error("Socket was not yet opened");

  ::close(_fd);
}

om::net::StreamSocket::~StreamSocket() {

  //this->close();
}
