//
//  Olli's C++ Library
//  net/agent.h
//  (c) 2012 Oliver Michel
//

#include <ctime>
#include <map>
#include <stdexcept>

#include <errno.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <om/net/io_interface.h>
#include <om/net/net.h>
#include <om/tools/random.h>
#include <om/tools/time.h>
#include <om/tools/tools.h>

#ifndef OM_NET_AGENT_H
#define OM_NET_AGENT_H

namespace om {
  namespace net {

    class Agent {

    public:

      enum timeout_mode_t { 
        timeout_mode_none         = 0, 
        timeout_mode_manual       = 1, 
        timeout_mode_uniform      = 2, 
        timeout_mode_exponential  = 3
      };

      Agent();
      Agent(const Agent& copy_from);
      Agent& operator=(const Agent& copy_from);

      // overrideable to add custom logic
      virtual void add_interface(IOInterface* iface) throw(std::logic_error);
      
      std::map<int, IOInterface*>* interfaces() const;
      std::map<int, IOInterface*> interfaces(IOInterface::iface_type type) const;

      void set_timeout_mode(timeout_mode_t t);
      timeout_mode_t timeout_mode() const;
      void set_manual_timeout(double t);
      double manual_timeout() const;
      void set_uniform_lower(double l);
      double uniform_lower() const;
      void set_uniform_upper(double u);
      double uniform_upper() const;
      void set_exponential_lambda(double l);
      double exponential_lambda() const;

      IOInterface* random_interface() const throw(std::logic_error);;
      IOInterface* random_interface(IOInterface::iface_type type) const
        throw(std::logic_error);
      IOInterface* interface_by_fd(int fd) const throw(std::logic_error);;

      void run() throw(std::runtime_error);
      
      virtual ~Agent();

    protected:
      
      fd_set _fds;
      fd_set _read_fds;
      int _fd_max;

      // callbacks
      virtual void device_ready(timeval* timestamp, IOInterface* iface) = 0;
      virtual void timeout_trigger(timeval* timestamp, timeval* timeout_tv) {}
      virtual void agent_start(timeval* timestamp) {}

    private:
      
      std::map<int, IOInterface*>* _interfaces;
      timeout_mode_t _timeout_mode;
      double _manual_timeout;
      double _uniform_lower;
      double _uniform_upper;
      double _exponential_lambda;
      timeval _current_timeout;

      void clean_iface_fds();
      void check_read_interfaces(timeval* timestamp);
      timeval next_timeout_timeval()
        throw(std::invalid_argument, std::logic_error);
    };
  }
}

#endif
