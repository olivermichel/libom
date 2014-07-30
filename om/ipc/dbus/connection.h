//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/connection.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_IPC_DBUS_CONNECTION_H
#define OM_IPC_DBUS_CONNECTION_H

#include <om/async/multiplex_interface.h>
#include <om/ipc/dbus/dbus.h>

#include <stdexcept>
#include <functional>
#include <map>
#include <dbus/dbus.h>

namespace om {
	namespace ipc {
		namespace dbus {
			
			class Connection : public async::MultiplexInterface {

				typedef std::function<DBusHandlerResult (om::ipc::dbus::Connection*, 
					DBusMessage*)> msg_handler;
			
			public:

				struct callback_context
				{
					callback_context();
					callback_context(Connection* c);
					Connection* connection;
				};

				Connection();

				void open(std::string addr, std::string req_name,
					std::function<void (om::ipc::dbus::Connection*)> connected_cb)
					throw(std::runtime_error, std::logic_error);

				void set_default_signal_handler(msg_handler cb);
				void set_default_method_call_handler(msg_handler cb);
				void set_default_method_return_handler(msg_handler cb);
				void set_default_error_handler(msg_handler cb);

				void set_method_call_handler(std::string iface, std::string method,
					msg_handler cb);

				DBusMessage* call_method_blocking(DBusMessage* msg)
					throw(std::runtime_error, std::logic_error);

				void send_message(DBusMessage* msg)
					throw(std::runtime_error, std::logic_error);

			protected:

				void ready(uint32_t events);

			private:

				DBusConnection* _conn;
				DBusWatch* _watch;
				callback_context _context;

				std::map<method_call_signature, msg_handler> _method_handlers;

				std::function<void (om::ipc::dbus::Connection*)> _connected_cb;

				msg_handler _default_signal_handler;
				msg_handler _default_method_call_handler;
				msg_handler _default_method_return_handler;
				msg_handler _default_error_handler;

				void _connected(DBusWatch* w)
					throw(std::logic_error);

				DBusHandlerResult _route_message(DBusMessage* msg);

				static DBusHandlerResult _message_filter(DBusConnection* conn,
					DBusMessage* msg, void* d);

				static unsigned _add_watch_static_callback(DBusWatch* w, void* d);
				static void _toggle_watch_static_callback(DBusWatch* w, void* d);
				static void _rm_watch_static_callback(DBusWatch* w, void* d);

				static DBusWatchFlags _epoll_to_dbus_watch_event(
					uint32_t epoll_events);
			};

		}
	}
}

#endif
