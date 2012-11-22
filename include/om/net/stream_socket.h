//
//  Olli's C++ Library
//  net/stream_socket.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_STREAM_SOCKET_H
#define OM_NET_STREAM_SOCKET_H

#include <stdexcept>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <om/net/net.h>
#include <om/net/socket.h>

namespace om {
  namespace net {

    class StreamSocket : public om::net::Socket {

    public:

      explicit StreamSocket(const om::net::tp_addr addr, 
        const std::string iface = "") 
        throw(std::runtime_error, std::invalid_argument);

      StreamSocket(const om::net::StreamSocket &copy_from);
      
      StreamSocket& operator=(StreamSocket& copy_from);

      int open(const om::net::tp_addr addr)
        throw(std::runtime_error, std::logic_error, std::invalid_argument);
        
      int open(const om::net::tp_addr addr, const std::string iface)
        throw(std::runtime_error, std::logic_error, std::invalid_argument);

      int send(const om::net::tp_addr remote_addr, 
        const unsigned char *tx_data, const size_t data_len);

      int receive(om::net::tp_addr *from, unsigned char *rx_buf, 
        const size_t buf_len);

      void close()
        throw(std::logic_error);
      
      ~StreamSocket();
    };
  }
}

#endif
