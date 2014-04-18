//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/datagram_socket.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//
//  implements a UDP socket
//


#ifndef OM_NET_DATAGRAM_SOCKET_H
#define OM_NET_DATAGRAM_SOCKET_H

#include <errno.h>
#include <functional>
#include <stdexcept>

#include <om/net/io_interface.h>

namespace om {
	namespace net {

		class DatagramSocket : public om::net::IOInterface {

		public:
			
			explicit DatagramSocket();

			explicit DatagramSocket(const om::net::tp_addr addr,
				std::function<void (om::net::DatagramSocket*)> read_handler) 
				throw(std::runtime_error, std::invalid_argument);

			int open(const om::net::tp_addr addr,
				std::function<void (om::net::DatagramSocket*)> read_handler)
				throw(std::runtime_error, std::logic_error, std::invalid_argument);

			// implement om::net::IOInterface
			void handle_read()
				throw(std::runtime_error, std::logic_error);

			int send(const om::net::tp_addr remote_addr, 
				const unsigned char *tx_data, const size_t data_len);

			int receive(om::net::tp_addr *from, unsigned char *rx_buf, 
				const size_t buf_len);

			void close()
				throw(std::logic_error);
			
			~DatagramSocket();

		private:

			om::net::tp_addr _addr;
			std::function<void (om::net::DatagramSocket*)> _read_handler;

			DatagramSocket(const om::net::DatagramSocket &copy_from);
			DatagramSocket& operator=(DatagramSocket& copy_from);
		};
	}
}

#endif
