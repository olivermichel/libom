
#ifndef OM_ASYNC_MULTIPLEX_INTERFACE_H
#define OM_ASYNC_MULTIPLEX_INTERFACE_H

namespace om {
	namespace async {

		class MultiplexInterface {

		public:

			MultiplexInterface();
			MultiplexInterface(int fd);
			MultiplexInterface(MultiplexInterface& copy_from) = delete;
			MultiplexInterface& operator=(MultiplexInterface& copy_from) = delete;

			int fd();

			virtual ~MultiplexInterface();

		protected:

			void set_fd(int fd);

		private:

			int _fd;
		};

	}
}

#endif
