//
//  Olli's C++ Library
//  net/socket.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_SOCKET_H
#define OM_NET_SOCKET_H

#include <stdexcept>
#include <iostream>
#include <cstring>

#include <sys/select.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <om/net/net.h>
#include <om/net/io_interface.h>

namespace om {
  namespace net {

    class Socket : public om::net::IOInterface {

    public:

      explicit Socket(const om::net::IOInterface::iface_type type,
        const om::net::tp_addr addr);
      
      Socket(const om::net::Socket &copy_from);
      
      Socket& operator=(Socket& copy_from);

      om::net::tp_addr addr();

      virtual int open(const om::net::tp_addr addr) = 0;

      virtual int send(const om::net::tp_addr remote_addr, 
        const unsigned char *tx_data, const size_t data_len) = 0;

      virtual int receive(om::net::tp_addr *from, unsigned char *rx_buffer, 
        const size_t buffer_len) = 0;

      virtual ~Socket() = 0;

    protected:
      om::net::tp_addr _addr;
    };
  }
}

#endif
