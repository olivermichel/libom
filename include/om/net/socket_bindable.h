//
//  Olli's C++ Library
//  net/socket_bindable.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_SOCKET_BINDABLE_H
#define OM_NET_SOCKET_BINDABLE_H

#include <stdexcept>
#include <iostream>
#include <string>

#include <cstdio>

#include <om/net/net.h>
#include <om/net/io_interface.h>

namespace om {
  namespace net {

    class SocketBindable 
      : private virtual om::net::IOInterface {

    public:
      void bind_to_iface(std::string iface) throw(std::runtime_error);

    protected:
      SocketBindable();

    private:
      std::string _bound_iface;
    };
  }
}

#endif
