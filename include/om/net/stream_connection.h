//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_connection.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//
//  available under the GNU General Public License v3
//  https://gnu.org/licenses/gpl.html
//
//  implements a TCP connection which can be used after an accept call
//

#ifndef OM_NET_STREAM_CONNECTION_H
#define OM_NET_STREAM_CONNECTION_H

#include <errno.h>
#include <unistd.h>

#include <om/net/agent.h>
#include <om/net/net.h>
#include <om/net/socket.h>

namespace om {
	namespace net {

		class StreamConnection : public om::net::Socket {
		
		public:

			// constructs a new StreamConnection object without attaching to a fd
			explicit StreamConnection();

			// constructs a new StreamConnection object and attaches to fd
			explicit StreamConnection(int fd)
				throw(std::logic_error, std::invalid_argument);

			explicit StreamConnection(int fd, om::net::tp_addr remote_addr)
				throw(std::logic_error, std::invalid_argument);

			// copy constructor
			StreamConnection(const om::net::StreamConnection &copy_from);

			// assignment copy constructor
			StreamConnection& operator=(StreamConnection& copy_from);

			// accessor for remote address
			om::net::tp_addr remote_addr();

			// attach object to an existing connection socket
			void attach(int fd)
				throw(std::logic_error, std::invalid_argument);

			void attach(int fd, om::net::tp_addr remote_addr)
				throw(std::logic_error, std::invalid_argument);

			// writes buf_len bytes out of tx_buf to the socket
			int send(const unsigned char* tx_buf, const size_t buf_len);

			// receives and writes buf_len Bytes from the socket into rx_buf
			int receive(unsigned char* rx_buf, const size_t buf_len);

			// closes the connection
			void close()
				throw(std::logic_error, std::runtime_error);

			// default destructor
			~StreamConnection();

		private:

			om::net::tp_addr _remote_addr;
		};
	}
}

#endif
