
#include "multiplexer.h"

om::async::Multiplexer::callback_context::callback_context()
	: interface(0) {}

om::async::Multiplexer::callback_context::callback_context(
	event_handler h, om::async::MultiplexInterface* i)
	: handler(h), interface(i) {}

om::async::Multiplexer::callback_context::callback_context(
	const om::async::Multiplexer::callback_context& copy_from)
	: handler(copy_from.handler), interface(copy_from.interface) {}

om::async::Multiplexer::Multiplexer() {}

void om::async::Multiplexer::set_timeout_generator(timeout_generator tg)
{
	_timeout_generator = tg;
}

void om::async::Multiplexer::set_timeout_callback(timeout_callback cb)
{
	_timeout_callback = cb;
}

void om::async::Multiplexer::add_interface(om::async::MultiplexInterface* iface, 
	event_handler handler)
	throw(std::logic_error)
{
	int fd = iface->fd();

	if(fd < 0)
		throw std::logic_error("Multiplexer: add_interface: not initialized");

	if(_fds.find(fd) == _fds.end())
		_fds.emplace(fd, callback_context(handler, iface));
	else
		throw std::logic_error("Multiplexer: add_interface: exists");
}

void om::async::Multiplexer::remove_interface(om::async::MultiplexInterface* iface)
	throw(std::runtime_error, std::logic_error)
{
	auto i = _fds.find(iface->fd());

	if(i != _fds.end())
		_fds.erase(i);
	else
		throw std::logic_error("Multiplexer: remove_interface: does not exist");
}

om::async::Multiplexer::~Multiplexer() {}
