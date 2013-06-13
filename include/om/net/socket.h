//
//  Olli's C++ Library
//  net/socket.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  
//  This class introduces an abstraction level for socket-like I/O devices.
//  To be extended with functions like packet/byte counters at some point.
//

#ifndef OM_NET_SOCKET_H
#define OM_NET_SOCKET_H

#include <om/net/net.h>
#include <om/net/io_interface.h>

namespace om {
	namespace net {

		class Socket : public om::net::IOInterface {

		public:

			explicit Socket(const om::net::IOInterface::iface_type type);
			explicit Socket(const om::net::Socket &copy_from);  
			Socket& operator=(Socket& copy_from);

			virtual ~Socket();
		};
	}
}

#endif
