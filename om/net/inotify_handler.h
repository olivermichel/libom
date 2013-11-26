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

#include <om/net/io_interface.h>
#include <map>

namespace om {
	namespace net {

		class INotifyHandler : public om::net::IOInterface {

		public:

			explicit INotifyHandler()
				throw(std::runtime_error);

			explicit INotifyHandler(const om::net::INotifyHandler& copy_from);  

			INotifyHandler& operator=(INotifyHandler& copy_from);

			int add_watch(std::string pathname, uint32_t mask)
				throw(std::runtime_error, std::logic_error);

			void remove_watch(int wd)
				throw(std::logic_error);

			ssize_t read_event(char* buf, size_t len)
				throw(std::runtime_error);

			std::string pathname_for_watch(int wd) const
				throw(std::logic_error);

			const std::map<int, std::string>* watches() const;

			virtual ~INotifyHandler();

		private:

			std::map<int, std::string>* _watches;
		};
	}
}

#endif
