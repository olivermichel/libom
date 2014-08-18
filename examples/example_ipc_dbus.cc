
#include <unistd.h>
#include <iostream>

#include <om/net/net.h>
#include <om/async/epoll_wrapper.h>
#include <om/async/multiplex_interface.h>

#include <om/ipc/dbus/dbus.h>
#include <om/ipc/dbus/message.h>
#include <om/ipc/dbus/connection.h>

#include <sys/epoll.h>


class DBusHandler {

public:

	DBusHandler() {}

	void read_stdin(int fd)
	{
		std::string buf;
		std::cin >> buf;
		std::cout << "read stdin: " << buf <<  std::endl;
	}

};


int main(int argc, char const *argv[])
{
	using namespace std::placeholders;

	om::async::EPollWrapper epoll;
	DBusHandler handler;

	epoll.dispatch();

	return 0;
}
