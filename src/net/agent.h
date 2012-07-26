//
//  Olli's C++ Library
//  net/agent.h
//  (c) 2012 Oliver Michel
//

#include <map>
#include <stdexcept>

#include <netinet/in.h>
#include <sys/select.h>

#include "net.h"
#include "io_interface.h"

#ifndef OM_NET_AGENT_H
#define OM_NET_AGENT_H

namespace om {
  namespace net {

    class Agent {

    enum timeout_mode_t { 
      timeout_mode_none         = 0, 
      timeout_mode_manual       = 1, 
      timeout_mode_uniform      = 2, 
      timeout_mode_exponential  = 3
    };

    public:
      Agent();
      Agent(const Agent& copy_from);
      Agent& operator=(const Agent& copy_from);

      void add_interface(IOInterface* iface) throw(std::logic_error);
      std::map<int, IOInterface*>* interfaces() const;
      
      void set_timeout_mode(timeout_mode_t t);
      timeout_mode_t timeout_mode() const;
      void set_manual_timeout(double t);
      double manual_timeout();
      void set_uniform_lower(double l);
      double uniform_lower();
      void set_uniform_upper(double u);
      double uniform_upper();
      void set_exponential_lambda(double l);
      double exponential_lambda();

      virtual void run();
      virtual ~Agent();

    protected:
      fd_set _fds;
      fd_set _read_fds;
      int _fd_max;

      virtual void device_ready(IOInterface* iface) = 0;
      virtual void timeout_triggered();

    private:
      std::map<int, IOInterface*>* _interfaces;
      timeout_mode_t _timeout_mode;
      double _manual_timeout;
      double _uniform_lower;
      double _uniform_upper;
      double _exponential_lambda;
    };
  }
}

#endif
