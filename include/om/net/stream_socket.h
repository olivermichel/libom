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

    };
  }
}

#endif
