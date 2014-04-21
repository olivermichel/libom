#include <iostream>
#include <unistd.h>

#include <om/net/dbus_adapter.h>

std::string bus;
std::string iface;

void connected(om::net::DBusAdapter* dbus)
{

//	dbus->send_signal	dbus->send_signal((

}


int main(int argc, char const *argv[]) 
{
	if(argc < 3) {
		std::cerr << "usage: dbus_send_sig <bus> <iface>" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	bus = std::string(argv[1]);
	iface = std::string(argv[2]);

	om::net::DBusAdapter dbus;

	dbus.connect(bus, "de.editum.omlib.dbus_send_sig", connected);

	return(EXIT_SUCCESS);
}

