
#ifndef OM_ASYNC_EPOLL_WRAPPER
#define OM_ASYNC_EPOLL_WRAPPER

#include "multiplex_interface.h"
#include "multiplexer.h"

#include <stdexcept>

namespace om {
	namespace async {

		class EPollWrapper : public Multiplexer {

		public:

			EPollWrapper(size_t size_hint = 8)
				throw(std::runtime_error);

			void add_interface(om::async::MultiplexInterface* iface,
				uint32_t events)
				throw(std::runtime_error, std::logic_error);

			void remove_interface(om::async::MultiplexInterface* iface)
				throw(std::runtime_error, std::logic_error);

			void add_descriptor(int fd, uint32_t events, event_handler handler)
				throw(std::runtime_error, std::logic_error);

			void remove_descriptor(int fd)
				throw(std::runtime_error, std::logic_error);

			void dispatch();

		private:

			int _epfd;
			static const size_t _qlen = 16;

			int _trigger_timeout(int timeout)
				throw(std::logic_error);
		};
	}
}

#endif
