//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/dbus_adapter.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_NET_DBUS_ADAPTER_H
#define OM_NET_DBUS_ADAPTER_H

#include <om/net/io_interface.h>

#include <dbus/dbus.h>
#include <stdexcept>
#include <string>

namespace om {
	namespace net {

		class DBusAdapter : public om::net::IOInterface {

		public:
			
			explicit DBusAdapter();

			void connect(std::string addr, std::string req_name)
				throw(std::runtime_error);

			void handle_read()
				throw(std::logic_error);

			void disconnect();

			std::string unique_name() const;

			~DBusAdapter();

		private:

			DBusConnection* _conn;
			std::string _unique_name;
		};
	}
}

#endif
