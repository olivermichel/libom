//
//  Olli's C++ Library
//  net/net.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_NET_H
#define OM_NET_NET_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include <om/tools/string.h>

namespace om {
  namespace net {

    class nw_addr {

    public:
      nw_addr();
      nw_addr(const char* addr) throw(std::invalid_argument);
      nw_addr(const std::string& addr) throw(std::invalid_argument);
      nw_addr(const unsigned char oct1, const unsigned char oct2, 
        const unsigned char oct3, const unsigned char oct4);
      nw_addr(const nw_addr& copy_from);

      nw_addr& operator=(const nw_addr& copy_from);
      nw_addr& operator=(const std::string addr);

      bool operator==(const nw_addr& other) const;
      bool operator<(const nw_addr& other) const;

      bool is_empty() const;

      std::string to_string() const;
      char* to_cstring() const;
      unsigned char* bytes() const;

    private:
      void read_string(std::string s);
      unsigned char _addr[4];
    };

    struct nw_pair {

      explicit nw_pair();
      explicit nw_pair(nw_addr src, nw_addr dst);
      explicit nw_pair(const nw_pair& copy_from);

      nw_pair& operator=(const nw_pair& copy_from);

      bool operator==(const nw_pair& other) const;
      bool operator<(const nw_pair& other) const;

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
      tp_addr(nw_addr addr, uint8_t proto, uint16_t port);
      tp_addr(const tp_addr& copy_from);

      tp_addr& operator=(const tp_addr& copy_from);

      bool operator==(const tp_addr& other) const;
      bool operator<(const tp_addr& other) const;

      void copy_bytes(unsigned char* dst) const;

      nw_addr addr;
      uint8_t proto;
      uint16_t port;
    };

    struct tp_pair {

      explicit tp_pair();
      explicit tp_pair(tp_addr src, tp_addr dst);
      explicit tp_pair(const tp_pair& copy_from);

      tp_pair& operator=(const tp_pair& copy_from);

      bool operator==(const tp_pair& other) const;
      bool operator<(const tp_pair& other) const;

      void copy_bytes(unsigned char* dst) const;

      tp_addr src;
      tp_addr dst;
    };

    void pack_i8(unsigned char *buf, unsigned int i);

    unsigned int unpack_i8(unsigned char *buf);

    void pack_i16(unsigned char *buf, unsigned int i);

    unsigned int unpack_i16(unsigned char *buf);
    
    void pack_i32(unsigned char *buf, unsigned long i);

    unsigned long unpack_i32(unsigned char *buf);

    void sockaddr_from_tp_addr(const tp_addr* ta, sockaddr_in* sa);

    void sockaddr_from_tp_addr(const tp_addr ta, sockaddr_in* sa);

    void sockaddr_from_nw_addr(const nw_addr* na, sockaddr_in* sa);

    void sockaddr_from_nw_addr(const nw_addr na, sockaddr_in* sa);

    void tp_addr_from_sockaddr(const sockaddr_in* sa, tp_addr* ta);

    void setup_ip_header(struct iphdr* header, char* src, char* dst, int proto, 
      size_t msg_len);
  }
}

#endif
