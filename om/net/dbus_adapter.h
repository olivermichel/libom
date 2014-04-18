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

		class DBusSignal {

		public:
			explicit DBusSignal(std::string addr, std::string iface, std::string name);
			explicit DBusSignal(const om::net::DBusSignal& copy_from);  
			DBusSignal& operator=(DBusSignal& copy_from);

		private:
			std::string _addr;
			std::string _iface;
			std::string _name;
		
			friend class DBusAdapter;
		};

		class DBusAdapter : public om::net::IOInterface {

		public:
			
			explicit DBusAdapter();

			void connect(std::string addr, std::string req_name)
				throw(std::runtime_error);

			void send_signal(DBusSignal& sig)
				throw(std::runtime_error);

			void handle_read()
				throw(std::logic_error);

			void disconnect();

			std::string unique_name() const;

			~DBusAdapter();

		private:

			DBusConnection* _conn;
			std::string _unique_name;

			explicit DBusAdapter(const om::net::DBusAdapter&);  
			DBusAdapter& operator=(DBusAdapter& copy_from);

			// static callback methods, receive pointer to current instance via d
			static unsigned _add_watch_static_callback(DBusWatch* w, void* d);
			static void _toggle_watch_static_callback(DBusWatch* w, void* d);
			static void _rm_watch_static_callback(DBusWatch* w, void* d);

			// wraps a pointer to an instance of DBusAdapter for passing
			// to dbus watch callbacks
			struct callback_context
			{
				callback_context() : adapter_instance(0) {};
				callback_context(DBusAdapter* a) : adapter_instance(a) {};
				DBusAdapter* adapter_instance;
			};
		};
	}
}

#endif
