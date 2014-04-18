//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/tunnel_device.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//  

#ifndef OM_NET_TUNNEL_DEVICE_H
#define OM_NET_TUNNEL_DEVICE_H

#include <stdexcept>
#include <string>
#include <om/net/io_interface.h>

namespace om {
	namespace net {

		class TunnelDevice : public om::net::IOInterface {

		public:
			
			explicit TunnelDevice();
			
			explicit TunnelDevice(std::string name)
				throw(std::runtime_error);

			short int flags();
			
			void set_flags(short int flags);

			int open()
				throw(std::runtime_error, std::logic_error);
			
			void close()
				throw(std::logic_error);

			int write(const unsigned char *tx_data, const size_t data_len);
			
			int read(unsigned char *rx_buf, const size_t buf_len);

			~TunnelDevice();

		private:
			
			std::string _name;
			short int _flags;

			TunnelDevice(const om::net::TunnelDevice &copy_from);
			TunnelDevice& operator=(TunnelDevice& copy_from);

		};
	}
}

#endif
