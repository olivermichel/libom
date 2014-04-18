//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  examples/example_net_dbus_adapter.cc
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include <iostream>
#include <unistd.h>

#include <om/net/agent.h>
#include <om/net/dbus_adapter.h>

class ExampleDBusAdapterAgent : public om::net::Agent {

public:

	void connected(om::net::DBusAdapter* dbus)
	{
		std::cout << "connected: " << dbus->unique_name() << std::endl;
		std::cout << "fd: " << dbus->fd() << std::endl;

		dbus->set_default_signal_handler(
			[this](om::net::DBusAdapter* dbus, DBusMessage* msg) { 
				this->receive_signal(dbus, msg); 
			}
		);

		dbus->match_signal("test.signal.Type",
			[this](om::net::DBusAdapter* dbus, DBusMessage* msg) { 
				this->receive_signal(dbus, msg); 
			}
		);

		om::net::DBusSignal sig(
			"/test/signal/Object", "test.signal.Type", "Test"
		);

		dbus->send_signal(sig);
	}

	void receive_signal(om::net::DBusAdapter* dbus, DBusMessage* msg)
	{
		std::cout << "receive_signal()" << std::endl;


		std::string iface(dbus_message_get_interface(msg));
		std::string sender(dbus_message_get_sender(msg));

		std::cout << "iface: " << iface << std::endl;
		std::cout << "sender: " << iface << std::endl;

	}

};

int main(int argc, char const *argv[]) {

	ExampleDBusAdapterAgent a;

	om::net::DBusAdapter* dbus = new om::net::DBusAdapter();

	try {
		dbus->connect("unix:path=/tmp/test_bus", "edu.colorado.cs.ngn.DBusTest",
			[&a](om::net::DBusAdapter* dbus) {
				a.add_interface(dbus), a.connected(dbus);
				a.run();
			}
		);

	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return 0;
}
