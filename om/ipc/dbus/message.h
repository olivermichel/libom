//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/message.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_IPC_DBUS_MESSAGE_H
#define OM_IPC_DBUS_MESSAGE_H

namespace om {
	namespace ipc {
		namespace dbus {

			class Message {

			public:
				
				Message();
				Message(Message& copy_from);

				Message& operator=(Message& copy_from);

				~Message();
			};
		}
	}
}

#endif