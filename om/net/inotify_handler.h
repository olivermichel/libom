//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  net/inotify_handler.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//  
//  This class abstracts a file descriptor handle returned by a inotify_init()
//  call. multiple watches may be added to this handler.
//

#ifndef OM_NET_INOTIFY_HANDLER_H
#define OM_NET_INOTIFY_HANDLER_H

#include <om/async/multiplex_interface.h>
#include <map>
#include <functional>

namespace om {
	namespace net {

		class INotifyHandler : public om::async::MultiplexInterface
		{

		public:

			explicit INotifyHandler()
				throw(std::runtime_error);

			INotifyHandler(const om::net::INotifyHandler&) = delete;
			INotifyHandler& operator=(INotifyHandler&) = delete;

			INotifyHandler(om::net::INotifyHandler&&) = default;
			INotifyHandler& operator=(INotifyHandler&&) = default;

			int add_watch(std::string pathname, uint32_t mask,
				std::function<void (struct inotify_event*)> handler)
				throw(std::runtime_error, std::logic_error);

			void remove_watch(int wd)
				throw(std::runtime_error, std::logic_error);

			// implement om::async::MultiplexInterface
			void ready()
				throw(std::runtime_error, std::logic_error);

			virtual ~INotifyHandler();

		private:

			ssize_t _read_event(char* buf, size_t len)
				throw(std::runtime_error);

			std::map<int, std::function<void (struct inotify_event*)> >* _watches;
		};
	}
}

#endif
