//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/stream_listener.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//
//  available under the GNU General Public License v3
//  https://gnu.org/licenses/gpl.html
//
//  implements a listening TCP socket which is delegating new incoming
//  connections to an om::net::Agent session
//

#ifndef OM_NET_STREAM_LISTENER_H
#define OM_NET_STREAM_LISTENER_H

#include <errno.h>
#include <unistd.h>

#include <om/net/agent.h>
#include <om/net/net.h>
#include <om/net/socket.h>

namespace om {
	namespace net {

		class StreamListener : public om::net::Socket {
			
			// constructs a new StreamListener object without opening a socket
			explicit StreamListener();

			// constructs a new StreamListener object and immediately opens 
			// the socket immediately
			explicit StreamListener(const om::net::tp_addr addr, 
				om::net::Agent* conn_handler) 
				throw(std::runtime_error, std::invalid_argument);

			// copy constructor
			StreamListener(const om::net::StreamListener &copy_from);

			// assignment copy constructor
			StreamListener& operator=(StreamListener& copy_from);

			// begins listening on a specified TCP port and passes new incoming
			// connections to an instance of om::net::Agent
			int open(const om::net::tp_addr addr, om::net::Agent* conn_handler)
				throw(std::runtime_error, std::logic_error, std::invalid_argument);

			// terminates the listener
			void close()
				throw(std::logic_error, std::runtime_error);
			
			// default destructor
			~StreamListener();

		private:
			
			om::net::tp_addr _addr;
			om::net::Agent* _conn_handler;
		};
	}
}

#endif
