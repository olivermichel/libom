//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_connection.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//
//  implements a TCP connection which can be used after an accept call
//

#ifndef OM_NET_STREAM_CONNECTION_H
#define OM_NET_STREAM_CONNECTION_H

#include <om/net/net.h>
#include <om/net/io_interface.h>
#include <ostream>

namespace om {
	namespace net {

		class StreamConnection : public om::net::IOInterface {
		
		public:

			// constructs a new StreamConnection object without attaching to a fd
			explicit StreamConnection();

			// constructs a new StreamConnection object and attaches to fd
			explicit StreamConnection(int fd)
				throw(std::logic_error, std::invalid_argument);

			explicit StreamConnection(int fd, om::net::tp_addr remote_addr)
				throw(std::logic_error, std::invalid_argument);

			// accessor for remote address
			om::net::tp_addr remote_addr();

			// attach object to an existing connection socket
			void attach(int fd)
				throw(std::logic_error, std::invalid_argument);

			void attach(int fd, om::net::tp_addr remote_addr)
				throw(std::logic_error, std::invalid_argument);

			// implement om::net::IOInterface
			void handle_read()
				throw(std::runtime_error, std::logic_error);

			// writes buf_len bytes out of tx_buf to the socket
			int send(const unsigned char* tx_buf, const size_t buf_len);

			// receives and writes buf_len Bytes from the socket into rx_buf
			int receive(unsigned char* rx_buf, const size_t buf_len);

			// closes the connection
			void close()
				throw(std::logic_error, std::runtime_error);

			// default destructor
			~StreamConnection();

			friend std::ostream& operator<<(std::ostream&, const StreamConnection&);

		private:

			om::net::tp_addr _remote_addr;

			StreamConnection(const om::net::StreamConnection &copy_from);
			StreamConnection& operator=(StreamConnection& copy_from);
		};
	}
}

#endif
