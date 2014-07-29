
#include "connection.h"

#include <sstream>
#include <iostream>
#include <sys/epoll.h>

om::ipc::dbus::Connection::callback_context::callback_context()
	: connection(0) {};

om::ipc::dbus::Connection::callback_context::callback_context(Connection* c)
	: connection(c) {};


om::ipc::dbus::Connection::Connection()
	: _conn(0), _watch(0), _context({0}), _method_handlers()
{
	_context.connection = this;
}

void om::ipc::dbus::Connection::open(std::string addr, std::string req_name,
	std::function<void (om::ipc::dbus::Connection*)> connected_cb)
	throw(std::runtime_error, std::logic_error)
{
	if(_conn)
		throw std::logic_error("Connection: open: already opened");

	if(!_default_signal_handler)
		throw std::logic_error("Connection: no default signal handler set");

	if(!_default_method_call_handler)
		throw std::logic_error("Connection: no default method call handler set");

	if(!_default_method_return_handler)
		throw std::logic_error("Connection: no default method return handler set");

	if(!_default_error_handler)
		throw std::logic_error("Connection: no default error handler set");

	DBusError err;
	dbus_error_init(&err);

	_conn = dbus_connection_open(addr.c_str(), &err);

	if(dbus_error_is_set(&err)) {
		throw std::runtime_error("Connection: connection error: "
			+ std::string(err.message));
		dbus_error_free(&err);
	}

	if(!_conn)
		throw std::runtime_error("Connection: connection error");

	dbus_bus_register(_conn, &err);

	int name_res = dbus_bus_request_name(_conn, req_name.c_str(), 0, &err);

	if(dbus_error_is_set(&err)) {
		throw std::runtime_error("Connection: request name error: "
			+ std::string(err.message));
		dbus_error_free(&err);
	}

	if(DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != name_res)
		throw std::runtime_error("Connection: request name error");

	_connected_cb = connected_cb;

	dbus_connection_add_filter(_conn, _message_filter, &_context, NULL);

	dbus_connection_set_watch_functions(
		_conn,
		_add_watch_static_callback,
		_toggle_watch_static_callback,
		_rm_watch_static_callback,
		&_context,
		NULL
	);
}

void om::ipc::dbus::Connection::set_default_signal_handler(msg_handler cb)
{
	_default_signal_handler = cb;
}

void om::ipc::dbus::Connection::set_default_method_call_handler(msg_handler cb)
{
	_default_method_call_handler = cb;
}

void om::ipc::dbus::Connection::set_default_method_return_handler(msg_handler cb)
{
	_default_method_return_handler = cb;
}

void om::ipc::dbus::Connection::set_default_error_handler(msg_handler cb)
{
	_default_error_handler = cb;
}

void om::ipc::dbus::Connection::set_method_call_handler(std::string iface,
	std::string method, msg_handler cb)
{
	if(_method_handlers.find(method_call_signature(iface, method)) 
		!= _method_handlers.end())
		throw std::logic_error("Connection: set_method_call_handler: "
			+ std::string("method already registered"));
	else
		_method_handlers.emplace(method_call_signature(iface, method), cb);
}

DBusMessage* om::ipc::dbus::Connection::call_method_blocking(DBusMessage* msg)
	throw(std::runtime_error, std::logic_error)
{
	DBusError err;
	DBusMessage* ret_msg;
	dbus_error_init(&err);

	if(!msg)
		throw std::logic_error("Connection: call_method_blocking: got null msg");

	ret_msg = dbus_connection_send_with_reply_and_block(_conn, msg, -1, &err);

	if(dbus_error_is_set(&err)) { 
		throw std::runtime_error("Connection: call_method_blocking: failed: "
			+ std::string(err.message));
		dbus_error_free(&err); 
	}

	if(!ret_msg)
		throw std::runtime_error("Connection: call_method_blocking: got null"
			+ std::string("response object"));

	return ret_msg;
}

void om::ipc::dbus::Connection::send_message(DBusMessage* msg)
	throw(std::runtime_error, std::logic_error)
{
	if(!msg)
		throw std::logic_error("Connection: call_method_blocking: got null msg");

	dbus_uint32_t serial = 2312; 

	if(!dbus_connection_send(_conn, msg, &serial))
		throw std::runtime_error("Connection: send_message: failed sending");
}

void om::ipc::dbus::Connection::ready(uint32_t events)
{
	dbus_watch_handle(_watch, _epoll_to_dbus_watch_event(events));

	while(dbus_connection_get_dispatch_status(_conn)
		== DBUS_DISPATCH_DATA_REMAINS) {
		
		dbus_connection_dispatch(_conn);
	}
}

void om::ipc::dbus::Connection::_connected(DBusWatch* w)
	throw(std::logic_error)
{
	_watch = w;

	if(MultiplexInterface::fd() != dbus_watch_get_unix_fd(w)) {
		MultiplexInterface::set_fd(dbus_watch_get_unix_fd(w));
		
		if(_connected_cb)
			_connected_cb(this);
		else
			throw std::logic_error("Connection: no connected handler set");
	}
}

DBusHandlerResult om::ipc::dbus::Connection::_route_message(DBusMessage* msg)
{
	if(dbus_message_get_type(msg) == DBUS_MESSAGE_TYPE_METHOD_CALL) {

		auto i = _method_handlers.find(method_call_signature(msg));
		
		if(i != _method_handlers.end())
			return i->second(this, msg);

		return _default_method_call_handler(this, msg);

	} else if(dbus_message_get_type(msg) == DBUS_MESSAGE_TYPE_METHOD_RETURN)
		return _default_method_return_handler(this, msg);
	else if(dbus_message_get_type(msg) == DBUS_MESSAGE_TYPE_SIGNAL)
		return _default_signal_handler(this, msg);
	else if(dbus_message_get_type(msg) == DBUS_MESSAGE_TYPE_ERROR)
		return _default_error_handler(this, msg);
	else
		return DBUS_HANDLER_RESULT_HANDLED;
}

DBusHandlerResult om::ipc::dbus::Connection::_message_filter(
	DBusConnection* conn, DBusMessage* msg, void* d)
{
	return ((callback_context*)d)->connection->_route_message(msg);
}

unsigned om::ipc::dbus::Connection::_add_watch_static_callback(
	DBusWatch* w, void* d)
{
	((callback_context*)d)->connection->_connected(w);
	return 1;
}

void om::ipc::dbus::Connection::_toggle_watch_static_callback(
	DBusWatch* w, void* d) {}

void om::ipc::dbus::Connection::_rm_watch_static_callback(
	DBusWatch* w, void* d) {}

DBusWatchFlags om::ipc::dbus::Connection::_epoll_to_dbus_watch_event(
	uint32_t epoll_events)
{
	if(epoll_events & EPOLLIN)
		return DBUS_WATCH_READABLE;
	else if(epoll_events & EPOLLOUT)
		return DBUS_WATCH_WRITABLE;
	else if(epoll_events & EPOLLHUP)
		return DBUS_WATCH_HANGUP;
	else
		return DBUS_WATCH_ERROR;
}
