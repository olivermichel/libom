//
//  Olli's C++ Library
//  net/raw_socket.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/raw_socket.h>
      
om::net::RawSocket::RawSocket(const int family, const int protocol)
  throw(std::runtime_error)
  : IOInterface(IOInterface::iface_type_sock_raw), _default_remote_addr(""),
    _default_remote_protocol(-1), _family(family), _protocol(protocol) {

  _fd = this->open(family, protocol);
}

om::net::RawSocket::RawSocket(const std::string default_remote_addr, 
  const int default_remote_protocol, const int family, const int protocol)
  throw(std::runtime_error, std::invalid_argument)
  : IOInterface(IOInterface::iface_type_sock_raw), 
    _default_remote_addr(default_remote_addr), 
    _default_remote_protocol(default_remote_protocol), 
    _family(family), _protocol(protocol) {

  _fd = this->open(family, protocol);
}

om::net::RawSocket::RawSocket(const om::net::RawSocket &copy_from)
  : IOInterface(IOInterface::iface_type_sock_raw),
    _default_remote_addr(copy_from._default_remote_addr),
    _default_remote_protocol(copy_from._default_remote_protocol),
    _family(copy_from._family), _protocol(copy_from._protocol) {

  _fd = copy_from._fd;
}

int om::net::RawSocket::send_raw(const char* tx_data, 
  const size_t data_len) {

  return this->send_raw(_default_remote_addr, tx_data, data_len);
}

int om::net::RawSocket::send_raw(const std::string remote_addr, 
  const char* tx_data, const size_t data_len) {

  struct sockaddr_in dst_addr;
  om::net::setup_addr_struct(&dst_addr, AF_INET, remote_addr, 0);

  int tx_bytes = sendto(_fd, tx_data, data_len, 0, 
    (struct sockaddr *)&dst_addr, sizeof(struct sockaddr));

  if(tx_bytes == -1)
    throw std::runtime_error("sendto(): " + std::string(strerror(errno)));

  return tx_bytes;
}

int om::net::RawSocket::receive(std::string *from, int* protocol, 
  unsigned char *rx_buf, const size_t buf_len) {

  return 0;
}

om::net::RawSocket::~RawSocket() {

  ::close(_fd);
}

int om::net::RawSocket::open(const int family, const int protocol)
  throw(std::runtime_error) {

  int fd = 0, yes = 1;

  if((fd = socket(family, SOCK_RAW, protocol)) == -1)
    throw std::runtime_error("socket(): " + std::string(strerror(errno)));

  if(setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &yes, sizeof(int)) == -1)
    throw std::runtime_error("setsockopt(): " + std::string(strerror(errno)));
  if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    throw std::runtime_error("setsockopt(): " + std::string(strerror(errno)));

  return fd;
}
