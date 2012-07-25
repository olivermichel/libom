//
//  Olli's C++ Library
//  net/net.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_NET_H
#define OM_NET_NET_H

#include <fcntl.h>
#include <linux/if_tun.h>
#include <net/if.h>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

namespace om {
  namespace net {

    enum transport_prototocol {
      tp_proto_undefined  = 0,
      tp_proto_tcp        = 1,
      tp_proto_udp        = 2,
      tp_proto_raw        = 3
    };

    struct ip_endpoint {
      
      explicit ip_endpoint() {}
      ip_endpoint(transport_prototocol tp_proto, std::string nw_addr, 
        int tp_addr);
      ip_endpoint(const ip_endpoint& copy_from);
      
      transport_prototocol tp_proto;
      std::string nw_addr;
      int tp_addr;
    };

    struct ip_pair {
      explicit ip_pair() {}
      ip_pair(ip_endpoint src, ip_endpoint dst);
      ip_pair(const ip_pair& copy_from);

      ip_endpoint src;
      ip_endpoint dst;
    };

    void pack_i8(unsigned char *buf, unsigned int i);
    unsigned int unpack_i8(unsigned char *buf);

    void pack_i16(unsigned char *buf, unsigned int i);
    unsigned int unpack_i16(unsigned char *buf);
    
    void pack_i32(unsigned char *buf, unsigned long i);
    unsigned long unpack_i32(unsigned char *buf);

    void setup_addr_struct(sockaddr_in *s, int family, std::string addr, 
      int port);

    void setup_addr_struct(sockaddr_in *s, ip_endpoint endpoint);

    void ip_endpoint_from_addr_struct(sockaddr_in *s, om::net::ip_endpoint *e);
  }
}

#endif
