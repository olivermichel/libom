//
//  Olli's C++ Library
//  net/socket_bindable.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_SOCKET_BINDABLE_H
#define OM_NET_SOCKET_BINDABLE_H

#include <iostream>
#include <stdexcept>
#include <string>

#include <cstdio>
#include <errno.h>
#include <net/if.h>

#include "io_interface.h"
#include "net.h"

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
