//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/message.cc
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include "message.h"

om::ipc::dbus::Message::Message() {}

om::ipc::dbus::Message::Message(Message& copy_from) {}

om::ipc::dbus::Message& om::ipc::dbus::Message::operator=(Message& copy_from)
{
	return *this;
}

om::ipc::dbus::Message::~Message() {}
