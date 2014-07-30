//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/message.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_IPC_DBUS_MESSAGE_H
#define OM_IPC_DBUS_MESSAGE_H

#include <dbus/dbus.h>
#include <stdexcept>
#include <string>
#include <om/ipc/dbus/connection.h>

namespace om {
	namespace ipc {
		namespace dbus {

			class Message {

			public:
	
				Message() = delete;
				Message(int type) throw (std::runtime_error);
				Message(Message& copy_from);

				Message& operator=(Message& copy_from);

				std::string destination();
				void set_destination(std::string destination);
				bool has_destination();
				std::string interface();
				void set_interface(std::string interface);
				bool has_interface();
				std::string member();
				void set_member(std::string member);
				bool has_member();
				std::string path();
				void set_path(std::string path);
				bool has_path();

				~Message();

			private:
				DBusMessage* _message;
				int _type;

				friend class Connection;
			};
		}
	}
}

#endif