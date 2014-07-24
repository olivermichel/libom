
#ifndef OM_ASYNC_EPOLL_WRAPPER
#define OM_ASYNC_EPOLL_WRAPPER

#include "multiplex_interface.h"

#include <functional>
#include <map>
#include <stdexcept>
#include <random>

namespace om {
	namespace async {

		class EPollWrapper {

		public:

			enum timeout_mode_t {
				timeout_mode_const,
				timeout_mode_poisson
			};

			EPollWrapper(size_t size_hint = 8)
				throw(std::runtime_error);

			EPollWrapper(EPollWrapper& copy_from) = delete;
			EPollWrapper& operator=(EPollWrapper& copy_from) = delete;

			timeout_mode_t timeout_mode();
			void set_timeout_mode(timeout_mode_t m);

			int timeout();
			void set_timeout(int const_timeout)
				throw(std::logic_error);

			int poisson_mean();
			void set_poisson_mean(int m);

			void set_timeout_callback(std::function<void (int)> timeout_callback);

			void add_interface(om::async::MultiplexInterface* iface, uint32_t events)
				throw(std::runtime_error, std::logic_error);

			void dispatch();

		private:

			int _epfd;
			timeout_mode_t _timeout_mode;
			int _timeout;
			std::poisson_distribution<int> _poisson;
			std::function<void (int)> _timeout_callback;
			std::map<int, om::async::MultiplexInterface*> _fds;
			std::default_random_engine _rand_generator;

			static const size_t _qlen = 16;
		};
	}
}

#endif
