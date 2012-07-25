//
//  Olli's C++ Library
//  net/net.cc
//  (c) 2012 Oliver Michel
//

#include "net.h"

om::net::ip_endpoint::ip_endpoint(transport_prototocol tp_proto, 
  std::string nw_addr, int tp_addr) 
  : tp_proto(tp_proto), nw_addr(nw_addr), tp_addr(tp_addr) {}

om::net::ip_endpoint::ip_endpoint(const ip_endpoint& copy_from)
  : tp_proto(copy_from.tp_proto), nw_addr(copy_from.nw_addr),
    tp_addr(copy_from.tp_addr) {}

om::net::ip_pair::ip_pair(ip_endpoint src, ip_endpoint dst) 
  : src(src), dst(dst) {}

om::net::ip_pair::ip_pair(const ip_pair& copy_from)
  : src(copy_from.src), dst(copy_from.dst) {}

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

void om::net::setup_addr_struct(sockaddr_in *s, om::net::ip_endpoint endpoint) {

  if(endpoint.nw_addr == "0.0.0.0") 
    // do not bind to specific IP
    s->sin_addr.s_addr = INADDR_ANY;
  else {

    // write string ip-address into sockaddr_in struct  
    //char addr_buf[16] = "";
    //strcpy(addr_buf, endpoint.nw_addr.c_str());
  
    inet_pton(AF_INET, endpoint.nw_addr.c_str(), &s->sin_addr);
  }

  s->sin_family = AF_INET;
  s->sin_port = htons(endpoint.tp_addr);
  memset(&(s->sin_zero), '\0', 8);
}

void om::net::ip_endpoint_from_addr_struct(sockaddr_in *s, 
  om::net::ip_endpoint *e) {

  e->nw_addr = std::string(inet_ntoa(s->sin_addr));
  e->tp_addr = ntohs(s->sin_port);
  e->tp_proto = om::net::tp_proto_undefined;
}

void om::net::setup_addr_struct(sockaddr_in *s, int family, 
  std::string addr, int port) {

  om::net::setup_addr_struct(s, 
    om::net::ip_endpoint(om::net::tp_proto_undefined, addr, port));
}
