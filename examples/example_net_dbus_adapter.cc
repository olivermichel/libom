//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  examples/example_net_dbus_adapter.cc
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#include <iostream>
#include <unistd.h>

#include <om/net/dbus_adapter.h>

int main(int argc, char const *argv[]) {

	om::net::DBusAdapter dbus;

	try {
		dbus.connect("unix:path=/tmp/test_bus", "edu.colorado.cs.ngn.DBusTest");
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::cout << "unique name: " << dbus.unique_name() << std::endl;


	

	// dbus.connect_system();

	// dbus.disconnect();

	return 0;
}
