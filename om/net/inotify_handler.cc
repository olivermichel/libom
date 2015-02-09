//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/inotify_handler.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include <cstring>
#include <sys/inotify.h>
#include <unistd.h>
#include <iostream>

#include <om/net/net.h>
#include <om/net/inotify_handler.h>

om::net::INotifyHandler::INotifyHandler()
	throw(std::runtime_error)
	:	om::async::MultiplexInterface(),
		_watches(new std::map<int, std::function<void (struct inotify_event*)> >()) 
{
	int fd = 0;
	// create new inotify instance
	if((fd = inotify_init()) < 0)
		throw std::runtime_error("inotify_init(): " + std::string(strerror(errno)));

	MultiplexInterface::set_fd(fd);
}

int om::net::INotifyHandler::add_watch(std::string pathname, uint32_t mask,
	std::function<void (struct inotify_event*)> handler)
	throw(std::runtime_error, std::logic_error)
{
	int wd = -1;

	if((wd = inotify_add_watch(MultiplexInterface::fd(), pathname.c_str(), mask)) < 0) {

		if(errno == ENOMEM || errno == ENOSPC)
			throw std::runtime_error("inotify_add_watch(): " 
				+ std::string(strerror(errno)));
		else
			throw std::logic_error("inotify_add_watch(): " 
				+ std::string(strerror(errno)));
	}

	_watches->insert(std::make_pair(wd, handler));
	return wd;
}

void om::net::INotifyHandler::remove_watch(int wd)
	throw(std::runtime_error, std::logic_error)
{
	std::map<int, std::function<void (struct inotify_event*)> >::iterator i;

	if((i = _watches->find(wd)) != _watches->end()) {

		if(inotify_rm_watch(MultiplexInterface::fd(), wd) < 0)
  			throw std::runtime_error("inotify_rm_watch(): "
  				+ std::string(strerror(errno)));
		
		_watches->erase(i);

	} else {
		throw std::logic_error("remove_watch(): wd was not registered: " + wd);
	}
}

void om::net::INotifyHandler::ready()
	throw(std::runtime_error, std::logic_error)
{
	ssize_t read_len = 0, parsed_len = 0;
	char buf[32 * (sizeof(struct inotify_event) + 256)];
	std::map<int, std::function<void (struct inotify_event*)> >::iterator watch;

	try {
		read_len = _read_event(buf, sizeof(buf));
	} catch(...) { throw; }

	while(parsed_len < read_len) {
		
		struct inotify_event* ev = (struct inotify_event*) &buf[parsed_len];
		parsed_len += sizeof(*ev) + ev->len;

		if((watch = _watches->find(ev->wd)) != _watches->end())
			watch->second(ev);
	}
}

ssize_t om::net::INotifyHandler::_read_event(char* buf, size_t len)
	throw(std::runtime_error)
{
	ssize_t read_len = -1;

	if((read_len = read(MultiplexInterface::fd(), buf, len)) < 0)
		throw std::runtime_error("read(): " + std::string(strerror(errno)));

	return read_len;
}

om::net::INotifyHandler::~INotifyHandler()
{
	for(auto watch = _watches->begin(); watch != _watches->end(); watch++) {

		this->remove_watch(watch->first);
	}
}
