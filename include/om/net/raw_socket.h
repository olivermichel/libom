//
//  Olli's C++ Library
//  net/raw_socket.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_RAW_SOCKET_H
#define OM_NET_RAW_SOCKET_H

#include <stdexcept>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

#include <om/net/net.h>
#include <om/net/io_interface.h>
#include <om/net/socket_bindable.h>

namespace om {
  namespace net {

    class RawSocket 
      : public virtual om::net::IOInterface, 
        public virtual om::net::SocketBindable {

    public:

      explicit RawSocket()
        throw(std::runtime_error);
      explicit RawSocket(const std::string default_remote_addr, 
        const int default_remote_protocol)
        throw(std::runtime_error, std::invalid_argument);
      RawSocket(const om::net::RawSocket &copy_from);

      int send_raw(const char* tx_data, const size_t data_len);
      int send_raw(const std::string remote_addr, const char* tx_data, 
        const size_t data_len);
      
      int receive(std::string *from, int* protocol, unsigned char *rx_buf, 
        const size_t buf_len);

      ~RawSocket();

    private:

      std::string _default_remote_addr;
      int _default_remote_protocol;
      int open() throw(std::runtime_error);
    };
  }
}

#endif
