
#include "epoll_wrapper.h"

#include <sys/epoll.h>
#include <string>
#include <cstring>
#include <iostream>

om::async::EPollWrapper::EPollWrapper(size_t size_hint)
	throw(std::runtime_error)
	:	_epfd(-1), 
		_timeout_mode(timeout_mode_const), 
		_timeout(-1),
		_timeout_callback(), 
		_fds(), 
		_rand_generator()
{
	if((_epfd = epoll_create(size_hint)) < 0)
		throw std::runtime_error("EPollWrapper: epoll_create: "
			+ std::string(strerror(errno)));
}

om::async::EPollWrapper::timeout_mode_t om::async::EPollWrapper::timeout_mode()
{
	return _timeout_mode;
}

void om::async::EPollWrapper::set_timeout_mode(EPollWrapper::timeout_mode_t m)
{
	_timeout_mode = m;
}

int om::async::EPollWrapper::timeout()
{
	return _timeout;
}

void om::async::EPollWrapper::set_timeout(int timeout)
	throw(std::logic_error)
{
	if(timeout != -1 && !_timeout_callback)
		throw std::logic_error("EPollWrapper: set_timeout: no callback specified");
	
	_timeout = timeout;
}

int om::async::EPollWrapper::poisson_mean()
{
	return _poisson.mean();
}

void om::async::EPollWrapper::set_poisson_mean(int m)
{
	_poisson = std::poisson_distribution<int>(m);
}

void om::async::EPollWrapper::set_timeout_callback(
	std::function<void (int)> timeout_callback)
{
	_timeout_callback = timeout_callback;
}

void om::async::EPollWrapper::add_interface(
	om::async::MultiplexInterface* iface, uint32_t events)
	throw(std::runtime_error, std::logic_error)
{
	struct epoll_event ev {0};
	int fd = iface->fd();

	if(fd < 0)
		throw std::logic_error("EPollWrapper: add_interface: "
			+ std::string("interface not initialized")
		);

	ev.events = events;
	ev.data.fd = fd;

	if(_fds.find(fd) == _fds.end()) {
		_fds.emplace(fd, iface);

		if(epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev) < 0) {

			if(errno == EEXIST || errno == ENOENT)
				throw std::logic_error("EPollWrapper: add_interface: "
					+ std::string("epoll_ctl: ")
					+ std::string(strerror(errno))
				);
			else
				throw std::runtime_error("EPollWrapper: add_interface: "
					+ std::string("epoll_ctl: ")
					+ std::string(strerror(errno))
				);
		}

	} else {
		std::cout << "duplicate fd: ignored" << std::endl;
	}
}

void om::async::EPollWrapper::dispatch()
{
	static struct epoll_event events[_qlen];

	while(1) {

		int epoll_timeout = 0;

		if(_timeout_mode == timeout_mode_const)
			epoll_timeout = _timeout;
		else if(_timeout_mode == timeout_mode_poisson)
			epoll_timeout = _poisson(_rand_generator);

		int nfds= epoll_wait(_epfd, events, _qlen, epoll_timeout);

		if(nfds < 0) {
			throw std::runtime_error("EPollWrapper: dispatch: "
				+ std::string("epoll_wait: ")
				+ std::string(strerror(errno))
			);
		} else if(nfds == 0) {
			_timeout_callback(_timeout);
		} else {

//			for(int i = 0; i < nfds; i++)
//				_fds[events[i].data.fd]->ready(events[i].events);
		}
	}
}
