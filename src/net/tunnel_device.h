//
//  Olli's C++ Library
//  net/tunnel_device.h
//  (c) 2012 Oliver Michel
//

#ifndef OM_NET_TUNNEL_DEVICE_H
#define OM_NET_TUNNEL_DEVICE_H

#include <string>

#include <errno.h>
#include <fcntl.h>
#include <linux/if_tun.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "net.h"
#include "io_interface.h"

namespace om {
  namespace net {

    class TunnelDevice : public om::net::IOInterface {

    public:
      
      explicit TunnelDevice();
      explicit TunnelDevice(std::string name) throw(std::runtime_error);

      short int flags();
      void set_flags(short int flags);

      int open() throw(std::runtime_error, std::logic_error);
      void close() throw(std::logic_error);

      int write(const unsigned char *tx_data, const size_t data_len);
      int read(unsigned char *rx_buf, const size_t buf_len);

      ~TunnelDevice();

    private:
      
      std::string _name;
      short int _flags;
    };
  }
}

#endif
