//
//  Olli's C++ Library
//  net/datagram_socket.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_DATAGRAM_SOCKET_H
#define OM_NET_DATAGRAM_SOCKET_H

#include <stdexcept>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <net/net.h>
#include <net/socket.h>

namespace om {
  namespace net {

    class DatagramSocket : public om::net::Socket {

    public:

      explicit DatagramSocket(const om::net::ip_pair addr_pair)
        throw(std::runtime_error, std::invalid_argument);
      explicit DatagramSocket(const om::net::ip_endpoint addr) 
        throw(std::runtime_error, std::invalid_argument);
      DatagramSocket(const om::net::DatagramSocket &copy_from);

      int open(const om::net::ip_endpoint addr)
        throw(std::runtime_error, std::logic_error, std::invalid_argument);

      int send(const unsigned char *tx_data, const size_t data_len);
      int send(const om::net::ip_endpoint remote_addr, 
        const unsigned char *tx_data, const size_t data_len);
      
      int receive(om::net::ip_endpoint *from, unsigned char *rx_buf, 
        const size_t buf_len);

      void close()
        throw(std::logic_error);
      ~DatagramSocket();
    };
  }
}

#endif
