//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/dbus_adapter.cc
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include <iostream>


#include "dbus_adapter.h"

om::net::DBusAdapter::DBusAdapter()
	: 	om::net::IOInterface(), 
		_conn(), 
		_unique_name(),
		_serial(0) {}

void om::net::DBusAdapter::connect(std::string addr, std::string req_name,
	std::function<void (om::net::DBusAdapter*)> connected_callback)
	throw(std::runtime_error, std::logic_error)
{
	const char* assign_name;

	_connected_callback = connected_callback;

	_open_connection(addr);
	_request_name(req_name);

	// query assigned unique name
   assign_name = dbus_bus_get_unique_name(_conn);

   if(assign_name != 0)
   	_unique_name = std::string(assign_name);
   else
   	throw std::runtime_error("DBusAdapter: failed getting unique name");

   _set_watch_functions();
}

void om::net::DBusAdapter::set_default_signal_handler(
	std::function<void (om::net::DBusAdapter*, DBusMessage*)> dsh)
{
	_default_signal_handler = dsh;
}

void om::net::DBusAdapter::match_signal(std::string iface,
	std::function<void (om::net::DBusAdapter*, DBusMessage*)> handler)
	throw(std::runtime_error)
{
	DBusError err;
	dbus_error_init(&err);

	std::string match_string = "type='signal',interface='" + iface + "'";

	dbus_bus_add_match(_conn, match_string.c_str(), &err);

	if(dbus_error_is_set(&err))
		throw std::runtime_error("DBusAdapter: failed matching signal: "
			+ std::string(err.message));
	else
		_signal_handlers[iface] = handler;

	dbus_connection_flush(_conn);
}

void om::net::DBusAdapter::send_signal(om::net::DBusSignal& sig)
	throw(std::runtime_error)
{
	DBusMessage* msg;

	msg = dbus_message_new_signal(sig._addr.c_str(), sig._iface.c_str(),
		sig._name.c_str());

	if(msg == 0)
		throw std::runtime_error("DBusAdapter: failed creating signal");

	if(!dbus_connection_send(_conn, msg, &(++_serial)))
		throw std::runtime_error("DBusAdapter: failed sending signal");

	dbus_connection_flush(_conn);
	dbus_message_unref(msg);
}

void om::net::DBusAdapter::handle_read()
	throw(std::logic_error)
{
	DBusMessage* msg;

	dbus_connection_read_write(_conn, 0);
	msg = dbus_connection_pop_message(_conn);

	switch(dbus_message_get_type(msg)) {
		
		case DBUS_MESSAGE_TYPE_METHOD_CALL:
			_handle_msg_method_call(msg);
			break;
		case DBUS_MESSAGE_TYPE_METHOD_RETURN:
			_handle_msg_method_return(msg);
			break;
		case DBUS_MESSAGE_TYPE_SIGNAL:
			_handle_msg_signal(msg);
			break;
		case DBUS_MESSAGE_TYPE_ERROR:
			_handle_msg_error(msg);
			break;

		default: std::cout << "unknown message" << std::endl; break;
	}

	dbus_message_unref(msg);
}

std::string om::net::DBusAdapter::unique_name() const
{
	return _unique_name;
}

void om::net::DBusAdapter::disconnect()
{
	dbus_connection_close(_conn);
}

om::net::DBusAdapter::~DBusAdapter()
{

}

void om::net::DBusAdapter::_open_connection(std::string addr)
	throw(std::runtime_error)
{
	DBusError err;
	dbus_error_init(&err);

	// open connection to the bus with provided address
	_conn = dbus_connection_open(addr.c_str(), &err);

	if(dbus_error_is_set(&err)) { 
		throw std::runtime_error("DBusAdapter: connection error: "
			+ std::string(err.message));
		dbus_error_free(&err); 
	}
	if(!_conn)
		throw std::runtime_error("DBusAdapter: connection error");

	// register connection on the bus
	dbus_bus_register(_conn, &err);
}

void om::net::DBusAdapter::_request_name(std::string name)
	throw(std::runtime_error)
{
	DBusError err;
	dbus_error_init(&err);

	// request specified name on the bus
	int name_res = dbus_bus_request_name(_conn, name.c_str(), 0, &err);

	if(dbus_error_is_set(&err)) {
		throw std::runtime_error("DBusAdapter: request name error: "
			+ std::string(err.message));
		dbus_error_free(&err);
	}
	if(DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != name_res)
		throw std::runtime_error("DBusAdapter: request name error");
}

void om::net::DBusAdapter::_set_watch_functions()
{
	callback_context data(this);

	dbus_connection_set_watch_functions(
		_conn,
		_add_watch_static_callback,
		_toggle_watch_static_callback,
		_rm_watch_static_callback,
		&data,
		NULL
	);
}

void om::net::DBusAdapter::_handle_msg_method_call(DBusMessage* msg)
{
	std::cout << "_handle_msg_method_call()" << std::endl;
}

void om::net::DBusAdapter::_handle_msg_method_return(DBusMessage* msg)
{
	std::cout << "_handle_msg_method_return()" << std::endl;
}

void om::net::DBusAdapter::_handle_msg_signal(DBusMessage* msg)
{
	std::string iface(dbus_message_get_interface(msg));	

	auto i = _signal_handlers.find(iface);

	if(i != _signal_handlers.end())
		i->second(this, msg);
	else
		_default_signal_handler(this, msg);
}

void om::net::DBusAdapter::_handle_msg_error(DBusMessage* msg)
{
	std::cout << "_handle_msg_error()" << std::endl;

	std::cout << "  error: " << dbus_message_get_error_name(msg) << std::endl;
}

unsigned om::net::DBusAdapter::_add_watch_static_callback(DBusWatch* w, void* d)
{
	int fd = dbus_watch_get_unix_fd(w);
	((callback_context*)d)->adapter_instance->_connected(fd);

	return 0;
}

void om::net::DBusAdapter::_toggle_watch_static_callback(DBusWatch* w, void* d)
{
	std::cout << "_toggle_watch_static_callback()" << std::endl;
}

void om::net::DBusAdapter::_rm_watch_static_callback(DBusWatch* w, void* d)
{
	std::cout << "_rm_watch_static_callback()" << std::endl;
}

void om::net::DBusAdapter::_connected(int fd)
	throw(std::logic_error)
{
	_fd = fd;

	if(_connected_callback)
		_connected_callback(this);
	else
		throw std::logic_error("DBusAdapter: no connected handler set");
}


om::net::DBusSignal::DBusSignal(std::string addr, std::string iface,
	std::string name)
	: _addr(addr), _iface(iface), _name(name) {}

om::net::DBusSignal::DBusSignal(const om::net::DBusSignal& copy_from)
	: _addr(copy_from._addr), _iface(copy_from._iface), _name(copy_from._name) {}

om::net::DBusSignal& om::net::DBusSignal::operator=(DBusSignal& copy_from)
{
	_addr = copy_from._addr;
	_iface = copy_from._iface;
	_name = copy_from._name;

	return *this;
}
