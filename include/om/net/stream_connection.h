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

			// constructs a new StreamConnection object without connecting to an fd
			explicit StreamConnection();

			// copy constructor
			StreamConnection(const om::net::StreamConnection &copy_from);

			// assignment copy constructor
			StreamConnection& operator=(StreamConnection& copy_from);


			// default destructor
			~StreamConnection();

		private:

			om::net::tp_addr _remote_addr;
		};
	}
}

#endif
