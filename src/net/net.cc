//
//  Olli's C++ Library
//  net/net.cc
//  (c) 2012 Oliver Michel
//

#include <om/net/net.h>

om::net::nw_addr::nw_addr() {

  _addr[0] = 0, _addr[1] = 0, _addr[2] = 0, _addr[3] = 0;
}

om::net::nw_addr::nw_addr(const std::string& addr) 
  throw(std::invalid_argument) {

  this->read_string(addr);
}

om::net::nw_addr::nw_addr(const char* addr) 
  throw(std::invalid_argument) {

  this->read_string(std::string(addr));
}

om::net::nw_addr::nw_addr(const unsigned char oct1, const unsigned char oct2, 
  const unsigned char oct3, const unsigned char oct4) {

  _addr[0] = oct1, _addr[1] = oct2, _addr[2] = oct3, _addr[3] = oct4;
}

om::net::nw_addr::nw_addr(const om::net::nw_addr& copy_from) {

  std::memcpy(&_addr, copy_from._addr, 4);
}

om::net::nw_addr& om::net::nw_addr::operator=(const om::net::nw_addr& copy_from) {

  std::memcpy(&_addr, copy_from._addr, 4);
  return *this;
}

om::net::nw_addr& om::net::nw_addr::operator=(const std::string addr) {

  _addr[0] = 0, _addr[1] = 0, _addr[2] = 0, _addr[3] = 0;
  return *this;
}

bool om::net::nw_addr::operator==(const om::net::nw_addr& other) const {

  return  _addr[0] == other._addr[0] && _addr[1] == other._addr[1] &&
          _addr[2] == other._addr[2] &&_addr[3] == other._addr[3];
}

bool om::net::nw_addr::operator<(const om::net::nw_addr& other) const {

  return  _addr[0] < other._addr[0] || _addr[1] < other._addr[1] ||
          _addr[2] < other._addr[2] || _addr[3] < other._addr[3];
}

void om::net::nw_addr::read_string(std::string s) {

  std::vector<std::string> v;
  om::tools::string::split(s, '.', v);

  if(v.size() != 4)
    throw std::invalid_argument("nw_addr(): invalid IPv4 address");

  for(size_t i = 0; i < 4; ++i) {
    unsigned int b = atoi(v[i].c_str());
    if(b >= 0 && b <= 255)
      _addr[i] = b & 0xff;
    else
      throw std::invalid_argument("nw_addr(): invalid IPv4 address");
  }
}

bool om::net::nw_addr::is_empty() const {

  return _addr[0] == 0 && _addr[1] == 0 && _addr[2] == 0 && _addr[3] == 0;
}

std::string om::net::nw_addr::to_string() const {

  std::stringstream s;
  s << (unsigned int) _addr[0] << '.' << (unsigned int) _addr[1] << '.';
  s << (unsigned int) _addr[2] << '.' << (unsigned int) _addr[3];
  return s.str();
}

char* om::net::nw_addr::to_cstring() const {

  return (char*)(to_string().c_str());
}

unsigned char* om::net::nw_addr::bytes() const {

  return (unsigned char*)_addr;
}

om::net::nw_pair::nw_pair()
  : src(), dst() {}

om::net::nw_pair::nw_pair(om::net::nw_addr src, om::net::nw_addr dst)
  : src(src), dst(dst) {}

om::net::nw_pair::nw_pair(const om::net::nw_pair& copy_from) 
  : src(copy_from.src), dst(copy_from.dst) {}

om::net::nw_pair& om::net::nw_pair::operator=(const om::net::nw_pair& copy_from) {

  src = copy_from.src, dst = copy_from.dst;
  return *this;
}

bool om::net::nw_pair::operator==(const om::net::nw_pair& other) const {

  return src == other.src && dst == other.dst;
}

bool om::net::nw_pair::operator<(const om::net::nw_pair& other) const {

  return src < other.src || dst < other.dst;
}

om::net::tp_addr::tp_addr()
  : addr(), proto(om::net::tp_proto_undefined), port(0) {}

om::net::tp_addr::tp_addr(om::net::nw_addr addr, uint8_t proto, uint16_t port) 
  : addr(addr), proto(proto), port(port) {}

om::net::tp_addr::tp_addr(const om::net::tp_addr& copy_from) 
  : addr(copy_from.addr), proto(copy_from.proto), port(copy_from.port) {}

om::net::tp_addr& om::net::tp_addr::operator=(const om::net::tp_addr& copy_from) {

  addr = copy_from.addr;
  proto = copy_from.proto;
  port = copy_from.port;

  return *this;
}

bool om::net::tp_addr::operator==(const om::net::tp_addr& other) const {

  return addr == other.addr && proto == other.proto && port == other.port;
}

bool om::net::tp_addr::operator<(const om::net::tp_addr& other) const {

  return addr < other.addr || proto < other.proto || port < other.port;
}

void om::net::tp_addr::copy_bytes(unsigned char* dst) const {

  std::memcpy(dst, addr.bytes(), 4);
  dst[4] = proto;
  dst[5] = port >> 8, dst[6] = port;
}

om::net::tp_pair::tp_pair()
  : src(), dst() {}

om::net::tp_pair::tp_pair(om::net::tp_addr src, om::net::tp_addr dst) 
  : src(src), dst(dst) {}

om::net::tp_pair::tp_pair(const om::net::tp_pair& copy_from) 
  : src(copy_from.src), dst(copy_from.dst) {}

om::net::tp_pair& om::net::tp_pair::operator=(const om::net::tp_pair& copy_from) {

  src = copy_from.src, dst = copy_from.dst;
  return *this;
}

bool om::net::tp_pair::operator==(const om::net::tp_pair& other) const {

  return src == other.src && dst == other.dst;
}

bool om::net::tp_pair::operator<(const om::net::tp_pair& other) const {

  return src < other.src || dst < other.dst;
}

void om::net::tp_pair::copy_bytes(unsigned char* dst) const {

  unsigned char buf1[7] = {0}, buf2[7] = {0};
  this->src.copy_bytes(buf1);
  this->src.copy_bytes(buf2);
  std::memcpy(dst, buf1, 7);
  std::memcpy(dst, buf2, 7);
}

void om::net::pack_i8(unsigned char *buf, unsigned int i) {

  *buf = i;
}

unsigned int om::net::unpack_i8(unsigned char *buf) {

  return buf[0];
}

void om::net::pack_i16(unsigned char *buf, unsigned int i) {

  *buf++ = i >> 8, *buf++ = i;
}

unsigned int om::net::unpack_i16(unsigned char *buf) {

  return (buf[0] << 8) | (buf[1]);
}

void om::net::pack_i32(unsigned char *buf, unsigned long i) {
  
  *buf++ = i >> 24, *buf++ = i >> 16, *buf++ = i >> 8, *buf++ = i;
}

unsigned long om::net::unpack_i32(unsigned char *buf) {

  return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]);
}

void om::net::sockaddr_from_tp_addr(const om::net::tp_addr* ta, sockaddr_in* sa) {

  if(ta->addr.is_empty())
    sa->sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, ta->addr.to_cstring(), &sa->sin_addr);

  sa->sin_family = AF_INET;
  sa->sin_port = htons(ta->port);
  memset(&(sa->sin_zero), '\0', 8);
}

void om::net::sockaddr_from_tp_addr(const om::net::tp_addr ta, sockaddr_in* sa) {

  if(ta.addr.is_empty())
    sa->sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, ta.addr.to_cstring(), &sa->sin_addr);

  sa->sin_family = AF_INET;
  sa->sin_port = htons(ta.port);
  memset(&(sa->sin_zero), '\0', 8);
}

void om::net::tp_addr_from_sockaddr(const sockaddr_in* sa, om::net::tp_addr* ta) {

  ta->addr = std::string(inet_ntoa(sa->sin_addr));
  ta->proto = om::net::tp_proto_undefined;
  ta->port = ntohs(sa->sin_port);
}

void om::net::sockaddr_from_nw_addr(const om::net::nw_addr* na, sockaddr_in* sa) {

  if(na->is_empty())
    sa->sin_addr.s_addr = INADDR_ANY;
  else 
    inet_pton(AF_INET, na->to_cstring(), &sa->sin_addr);

  sa->sin_port = 0;  
  sa->sin_family = AF_INET;
  memset(&(sa->sin_zero), '\0', 8);
}

void om::net::sockaddr_from_nw_addr(const om::net::nw_addr na, sockaddr_in* sa) {

  if(na.is_empty())
    sa->sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, na.to_cstring(), &sa->sin_addr);

  sa->sin_port = 0;
  sa->sin_family = AF_INET;
  memset(&(sa->sin_zero), '\0', 8);
}

void om::net::setup_ip_header(struct iphdr* header, char* src, char* dst, 
  int proto, size_t msg_len) {

  header->ihl = sizeof(struct iphdr)/4;
  header->version = 4;
  header->tos = 0;
  header->tot_len = sizeof(struct iphdr) + msg_len;
  header->id = htons(rand());
  header->frag_off = 0;
  header->ttl = 255;
  header->protocol = proto;
  header->check = 0;
  header->saddr = inet_addr(src);
  header->daddr = inet_addr(dst);
}
