//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_client.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//
//  implements the client side of a TCP socket, compatible with om::net::Agent
//

#ifndef OM_NET_STREAM_CLIENT_H
#define OM_NET_STREAM_CLIENT_H

#include <errno.h>
#include <unistd.h>

#include <om/net/net.h>
#include <om/net/socket.h>

namespace om {
	namespace net {

		class StreamClient : public om::net::Socket {

		public:

			// constructs a new StreamClient object without opening a connection
			explicit StreamClient();

			// constructs a new StreamClient object and immediately opens a
			// connection to remote_addr
			explicit StreamClient(const om::net::tp_addr remote_addr) 
				throw(std::runtime_error, std::invalid_argument);
			
			// copy constructor
			StreamClient(const om::net::StreamClient &copy_from);			

			// assignment copy constructor
			StreamClient& operator=(StreamClient& copy_from);

			// opens a new TCP connection to remote_addr, throws runtime_error if
			// the connection establishment fails, logic_error if the connection has
			// been opened already or invalid_argument if remote_address is corrupt,
			// returns the file describtor of the new connection upon success
			int open(const om::net::tp_addr remote_addr)
				throw(std::runtime_error, std::logic_error, std::invalid_argument);

			// writes buf_len bytes out of tx_buf to the socket
			int send(const unsigned char* tx_buf, const size_t buf_len);

			// receives and writes buf_len Bytes from the socket into rx_buf
			int receive(unsigned char* rx_buf, const size_t buf_len);

			// closes the connection
			void close()
				throw(std::logic_error, std::runtime_error);
			
			// default destructor
			~StreamClient();

		private:
			
			om::net::tp_addr _remote_addr;
		};
	}
}

#endif
