//
//  Olli's C++ Library
//  net/tunnel_device.cc
//  (c) 2012 Oliver Michel
//

#include "tunnel_device.h"

om::net::TunnelDevice::TunnelDevice()
  : om::net::IOInterface(om::net::IOInterface::iface_type_tun),
    _flags(IFF_TUN | IFF_NO_PI) {}

om::net::TunnelDevice::TunnelDevice(std::string name) 
  throw(std::runtime_error) 
  : om::net::IOInterface(om::net::IOInterface::iface_type_tun), _name(name),
    _flags(IFF_TUN | IFF_NO_PI) {
  
  this->open();
}

short int om::net::TunnelDevice::flags() {

  return _flags;
}

void om::net::TunnelDevice::set_flags(short int flags) {

  _flags = flags;
}

int om::net::TunnelDevice::open() 
  throw(std::runtime_error, std::logic_error) {

  if(_fd != 0) throw std::logic_error("Device already opened");

  struct ifreq ifr;
  int fd = -1;
  char tun_name[IFNAMSIZ];
  strcpy(tun_name, _name.c_str());
  
  // open tunnel device
  if((fd = ::open("/dev/net/tun", O_RDWR)) < 0)
    throw std::runtime_error("cannot open /dev/net/tun: " 
      + std::string(strerror(errno)));

  // set up interface request
  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_name, tun_name, IFNAMSIZ);
  ifr.ifr_flags = _flags;

  // request interface
  if((ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
    ::close(fd);
    throw std::runtime_error("ioctl(): failed requesting virtual interface: " 
      + std::string(strerror(errno)));
  }

  _fd = fd;
  
  return fd;
}

int om::net::TunnelDevice::write(const unsigned char *tx_data, 
  const size_t data_len) {

  return ::write(_fd, tx_data, data_len);
}
      
int om::net::TunnelDevice::read(unsigned char *rx_buf, const size_t buf_len) {

  return ::read(_fd, rx_buf, buf_len);
}

void om::net::TunnelDevice::close() 
  throw(std::logic_error) { }

om::net::TunnelDevice::~TunnelDevice() { }
