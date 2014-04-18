//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/dbus_connection.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_NET_DBUS_CONNECTION_H
#define OM_NET_DBUS_CONNECTION_H

#include <om/net/io_interface.h>

#include <dbus/dbus.h>

namespace om {
	namespace net {

		class DBusConnection : public om::net::IOInterface {

		public:
			
			explicit DBusConnection();

			~DBusConnection();

		private:

			::DBusConnection* _conn;
		};
	}
}

#endif
