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
		std::cout << "connected(): " << std::endl;
		std::cout << "  unique name: " << dbus->unique_name() << std::endl;

		dbus->set_default_signal_handler(
			[this](om::net::DBusAdapter* dbus, DBusMessage* msg) { 
				this->receive_signal(dbus, msg); 
			}
		);

		dbus->set_default_method_call_handler(
			[this](om::net::DBusAdapter* dbus, DBusMessage* msg) { 
				this->receive_method_call(dbus, msg); 
			}
		);

		dbus->match_signal("edu.colorado.cs.ngn.sdipc.test",
			[this](om::net::DBusAdapter* dbus, DBusMessage* msg) { 
				this->receive_signal(dbus, msg); 
			}
		);

		dbus->match_method_call("edu.colorado.cs.ngn.sdipc.TestInterface",
			[this](om::net::DBusAdapter* dbus, DBusMessage* msg) { 
				 this->receive_method_call(dbus, msg);
			}
		);

		om::net::DBusMethodCall method(
			"edu.colorado.cs.ngn.sdipc.client1",
			"edu.colorado.cs.ngn.sdipc.TestInterface",
			"/edu/colorado/cs/ngn/sdipc/TestObject",
			"Hi"
		);

		dbus->call_method(method);
	}

	void receive_signal(om::net::DBusAdapter* dbus, DBusMessage* msg)
	{
		std::cout << "receive_signal():" << std::endl;

		std::string iface(dbus_message_get_interface(msg));
		std::string path(dbus_message_get_path(msg));
		std::string sender(dbus_message_get_sender(msg));
		std::string member(dbus_message_get_member(msg));

		std::cout << "  iface:  " << iface << std::endl;
		std::cout << "  path:   " << path << std::endl;
		std::cout << "  sender: " << sender << std::endl;
		std::cout << "  member: " << member << std::endl;
	}

	void receive_method_call(om::net::DBusAdapter* dbus, DBusMessage* msg)
	{
		std::cout << "receive_method_call():" << std::endl;

		std::string iface(dbus_message_get_interface(msg));
		std::string path(dbus_message_get_path(msg));
		std::string sender(dbus_message_get_sender(msg));
		std::string member(dbus_message_get_member(msg));

		std::cout << "  iface:  " << iface << std::endl;
		std::cout << "  path:   " << path << std::endl;
		std::cout << "  sender: " << sender << std::endl;
		std::cout << "  member: " << member << std::endl;
	}

};

int main(int argc, char const *argv[]) {

	if(argc < 2) {
		std::cerr << "usage: example_net_dbus_adapter name" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string name = argv[1];

	ExampleDBusAdapterAgent a;

	om::net::DBusAdapter* dbus = new om::net::DBusAdapter();

	try {
		dbus->connect("unix:path=/tmp/test_bus", name,
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
