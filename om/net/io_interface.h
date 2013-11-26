//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/io_interface.h
//  (c) 2012 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//
//  Provides an abstraction for I/O interfaces compatible with om::net::Agent
//

#ifndef OM_NET_IO_INTERFACE_H
#define OM_NET_IO_INTERFACE_H

#include <stdexcept>
#include <sys/select.h>

#include <om/net/net.h>

namespace om {
	namespace net {

		class IOInterface {

		public:

			enum iface_type {
				iface_type_unknown,
				iface_type_sock_raw,
				iface_type_sock_stream,
				iface_type_sock_dgram,
				iface_type_tun,
				iface_type_inotify_handler
			};

			explicit IOInterface(iface_type type);
			IOInterface(const IOInterface& copy_from);
			IOInterface& operator=(const IOInterface& copy_from);

			int fd();

			void add_to_fd_set(fd_set *fds) throw(std::logic_error);
			void remove_from_fd_set(fd_set *fds) throw(std::logic_error);

			iface_type type();

			virtual void close() {}
			virtual ~IOInterface() {}
		
		protected:
			int _fd;

		private:
			iface_type _iface_type;
		};
	}
}

#endif
