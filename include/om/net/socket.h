//
//  Olli's C++ Library
//  net/socket.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_SOCKET_H
#define OM_NET_SOCKET_H

#include <stdexcept>
#include <iostream>

#include <sys/select.h>

#include <om/net/net.h>
#include <om/net/io_interface.h>

namespace om {
  namespace net {

    class Socket : public om::net::IOInterface {

    public:

      explicit Socket(const om::net::IOInterface::iface_type type, 
        const om::net::ip_pair ip_pair);
      explicit Socket(const om::net::IOInterface::iface_type type, 
        const om::net::ip_endpoint addr);
      Socket(const om::net::Socket &copy_from);

      om::net::ip_endpoint addr();
      om::net::ip_endpoint default_remote_addr();

      void set_default_remote_addr(const om::net::ip_endpoint remote);

      virtual int open(const om::net::ip_endpoint addr) = 0;
      
      virtual int send(const unsigned char *tx_data, const size_t data_len) = 0;
      virtual int send(const om::net::ip_endpoint remote_addr, 
        const unsigned char *tx_data, const size_t data_len) = 0;
      
      virtual int receive(om::net::ip_endpoint *from, unsigned char *rx_buffer, 
        const size_t buffer_len) = 0;

      virtual ~Socket() = 0;

    protected:
      om::net::ip_endpoint _addr;
      om::net::ip_endpoint _default_remote_addr;
    };
  }
}

#endif
