//
//  Olli's C++ Library
//  net/stream_client.h
//  (c) 2013 Oliver Michel
//

#ifndef OM_NET_STREAM_CLIENT_H
#define OM_NET_STREAM_CLIENT_H

#include <stdexcept>
#include <string>

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <om/net/net.h>
#include <om/net/socket.h>

namespace om {
  namespace net {

    class StreamClient : public om::net::Socket {

      explicit StreamClient(const om::net::tp_addr addr, 
        const om::net::tp_addr server_addr) 
        throw(std::runtime_error, std::invalid_argument);

      StreamClient(const om::net::StreamClient &copy_from);
      
      StreamClient& operator=(StreamClient& copy_from);

      int open(const om::net::tp_addr server_addr)
        throw(std::runtime_error, std::logic_error, std::invalid_argument);

      void close()
        throw(std::logic_error);
      
      ~StreamClient();

private:
      om::net::tp_addr _server_addr;

    };
  }
}

#endif
