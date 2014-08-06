
#include "test.h"

#include <om/ipc/dbus/message.h>

int main()
{

	om::ipc::dbus::Message msg(DBUS_MESSAGE_TYPE_SIGNAL);
	

	test::set_name("ipc::dbus::Message");

	test::expect_false<bool>(msg.has_member(), 
		"has_interface() responds correcly on false");	
	msg.set_interface("de.editum.test");
	test::expect_equal<std::string>(msg.interface(), "de.editum.test",
		"sets and retrievesthe interface name");
	test::expect_true<bool>(msg.has_interface(), 
		"has_interface() responds correcly");

	test::expect_false<bool>(msg.has_member(), 
		"has_member() responds correcly on false");
	msg.set_member("Test");
	test::expect_equal<std::string>(msg.member(), "Test",
		"sets and retrieves the member name");
	test::expect_true<bool>(msg.has_member(), 
		"has_member() responds correcly on true");

	test::expect_false<bool>(msg.has_destination(), 
		"has_destination() responds correcly on false");
	msg.set_destination("de.editum.test");
	test::expect_equal<std::string>(msg.destination(), "de.editum.test",
		"sets and retrieves the destination name");
	test::expect_true<bool>(msg.has_destination(), 
		"has_destination() responds correcly on true");

	test::expect_false<bool>(msg.has_path(), 
		"has_path() responds correcly on false");
	msg.set_path("/de/editum/test");
	test::expect_equal<std::string>(msg.path(), "/de/editum/test",
		"sets and retrieves the path name");
	test::expect_true<bool>(msg.has_path(), 
		"has_path() responds correcly on true");

	return 0;

}
