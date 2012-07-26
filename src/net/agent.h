//
//  Olli's C++ Library
//  net/agent.h
//  (c) 2012 Oliver Michel
//

#include <map>

#include <netinet/in.h>
#include <sys/select.h>

#include "net.h"
#include "io_interface.h"

#ifndef OM_NET_AGENT_H
#define OM_NET_AGENT_H

namespace om {
  namespace net {

    class Agent {

    public:
      Agent();
      Agent(const Agent& copy_from);
      Agent& operator=(const Agent& copy_from);

      void add_interface(IOInterface* iface);
      virtual void run();
      virtual ~Agent();

    protected:
      fd_set _fds;
      fd_set _read_fds;
      int _fd_max;
      std::map<int, IOInterface>* interfaces();
      virtual void receive_from_device(IOInterface* iface) = 0;

    private:
      std::map<int, IOInterface>* _interfaces;
    };
  }
}

#endif
