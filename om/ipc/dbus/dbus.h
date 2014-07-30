//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/dbus.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_IPC_DBUS_DBUS_H
#define OM_IPC_DBUS_DBUS_H

#include <dbus/dbus.h>

#include <stdexcept>
#include <string>

namespace om {
	namespace ipc {
		namespace dbus {

			void init_msg_read_iter(DBusMessageIter* iter, DBusMessage* msg)
				throw(std::logic_error);

			std::string read_string(DBusMessageIter* iter, DBusMessage* msg)
				throw(std::logic_error);


			std::string msg_summary(DBusMessage* msg);

			struct method_call_signature
			{
				method_call_signature();
				method_call_signature(std::string i, std::string m);
				method_call_signature(DBusMessage* msg);

				bool operator==(const method_call_signature& other) const;
				bool operator<(const method_call_signature& other) const;

				std::string iface;
				std::string method;
			};
		}
	}
}

#endif
