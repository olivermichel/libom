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
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>

#include <om/tools/string.h>

namespace om {
  namespace net {

    class nw_addr {
    public:
      nw_addr();
      nw_addr(const char* addr) throw(std::invalid_argument);
      nw_addr(const std::string& addr) throw(std::invalid_argument);
      nw_addr(const nw_addr& copy_from);
      nw_addr& operator=(nw_addr&);
      nw_addr& operator=(std::string addr);
      bool is_empty();
      std::string to_string();
      char* to_cstring();
    private:
      void read_string(std::string s);
      unsigned char _addr[4];
    };

    struct nw_pair {
      explicit nw_pair();
      explicit nw_pair(nw_addr src, nw_addr dst);
      explicit nw_pair(const nw_pair& copy_from);
      nw_pair& operator=(nw_pair&);
      nw_addr src;
      nw_addr dst;
    };

    enum tp_proto {
      tp_proto_tcp        = 0x6,
      tp_proto_udp        = 0x11,
      tp_proto_undefined  = 0xff
    };

    struct tp_addr {
      tp_addr();
      tp_addr(nw_addr addr, tp_proto proto, int port);
      tp_addr(const tp_addr& copy_from);
      tp_addr& operator=(tp_addr&);
      nw_addr addr;
      tp_proto proto;
      int port;
    };

    struct tp_pair {
      explicit tp_pair();
      explicit tp_pair(tp_addr src, tp_addr dst);
      explicit tp_pair(const tp_pair& copy_from);
      tp_pair& operator=(tp_pair&);
      tp_addr src;
      tp_addr dst;
    };

    struct ip_endpoint {
      
      explicit ip_endpoint() {}
      ip_endpoint(tp_proto proto, std::string nw_addr, 
        int tp_addr);
      ip_endpoint(const ip_endpoint& copy_from);
      
      tp_proto proto;
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

    void sockaddr_from_tp_addr(tp_addr* ta, sockaddr_in* sa);

    void sockaddr_from_tp_addr(tp_addr ta, sockaddr_in* sa);

    void tp_addr_from_sockaddr(sockaddr_in* sa, tp_addr* ta);

    // DEPRECATED
    void setup_addr_struct(sockaddr_in *s, int family, std::string addr, 
      int port);

    // DEPRECATED
    void setup_addr_struct(sockaddr_in *s, ip_endpoint endpoint);

    // DEPRECATED
    void ip_endpoint_from_addr_struct(sockaddr_in *s, om::net::ip_endpoint *e);

    void setup_ip_header(struct iphdr* header, char* src, char* dst, int proto, 
      size_t msg_len);
  }
}

#endif
