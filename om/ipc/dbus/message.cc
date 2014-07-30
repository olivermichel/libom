//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/message.cc
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include "message.h"

om::ipc::dbus::Message::Message(int type)
	throw(std::runtime_error)
	: 	_message(0), 
		_type(type)
{
	if(!(_message = dbus_message_new(_type)))
		throw std::runtime_error("Message: not enough memory");
}

om::ipc::dbus::Message::Message(Message& copy_from)
	: 	_message(dbus_message_copy(copy_from._message)),
		_type(copy_from._type)
{

}

om::ipc::dbus::Message& om::ipc::dbus::Message::operator=(Message& copy_from)
{
	_message = dbus_message_copy(copy_from._message);
	_type = copy_from._type;

	return *this;
}

std::string om::ipc::dbus::Message::destination()
{
	const char* destination = dbus_message_get_destination(_message);
	return destination ? std::string(destination) : std::string();
}

void om::ipc::dbus::Message::set_destination(std::string destination)
{
	dbus_message_set_destination(_message, destination.c_str());
}

bool om::ipc::dbus::Message::has_destination()
{
	return dbus_message_get_destination(_message) ? true : false;
}

std::string om::ipc::dbus::Message::interface()
{
	const char* interface = dbus_message_get_interface(_message);
	return interface ? std::string(interface) : std::string();
}

void om::ipc::dbus::Message::set_interface(std::string interface)
{
	dbus_message_set_interface(_message, interface.c_str());
}

bool om::ipc::dbus::Message::has_interface()
{
	return dbus_message_get_interface(_message) ? true : false;
}

std::string om::ipc::dbus::Message::member()
{
	const char* member = dbus_message_get_member(_message);
	return member ? std::string(member) : std::string();
}

void om::ipc::dbus::Message::set_member(std::string member)
{
	dbus_message_set_member(_message, member.c_str());
}

bool om::ipc::dbus::Message::has_member()
{
	return dbus_message_get_member(_message) ? true : false;
}

std::string om::ipc::dbus::Message::path()
{
	const char* path = dbus_message_get_path(_message);
	return path ? std::string(path) : std::string();
}

void om::ipc::dbus::Message::set_path(std::string path)
{
	dbus_message_set_path(_message, path.c_str());
}

bool om::ipc::dbus::Message::has_path()
{
	return dbus_message_get_path(_message) ? true : false;
}

om::ipc::dbus::Message::~Message()
{
	if(_message != 0)
		dbus_message_unref(_message);
}
