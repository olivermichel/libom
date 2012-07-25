//
//  Olli's C++ Library
//  net/io_interface.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_IO_INTERFACE_H
#define OM_NET_IO_INTERFACE_H

#include <stdexcept>

#include <sys/select.h>

#include "net.h"

namespace om {
  namespace net {

    class IOInterface {

    public:
      IOInterface();
      IOInterface(const IOInterface &copy_from);

      int fd();

      void add_to_fd_set(fd_set *fds) throw(std::logic_error);
      void remove_from_fd_set(fd_set *fds) throw(std::logic_error);

      virtual void close() = 0;
      virtual ~IOInterface() = 0;
    
    protected:
      int _fd;
    };
  }
}

#endif
