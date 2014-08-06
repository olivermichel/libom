//
//  Olli's C++ Library [https://bitbucket.org/omichel/om-lib]
//  ipc/dbus/message.h
//  (c) 2014 Oliver Michel <oliver dot michel at editum dot de>
//  http://ngn.cs.colorado/~oliver
//

#ifndef OM_IPC_DBUS_MESSAGE_H
#define OM_IPC_DBUS_MESSAGE_H

#include <dbus/dbus.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <om/ipc/dbus/connection.h>
#include <typeinfo>

namespace om {
	namespace ipc {
		namespace dbus {

			class Message {

			public:
	
				Message() = delete;
				Message(int type) throw (std::runtime_error);
				Message(int type, std::string destination, std::string interface,
					std::string member) throw (std::runtime_error);
				
				Message(Message& copy_from);

				Message& operator=(Message& copy_from);

				std::string destination();
				void set_destination(std::string destination);
				bool has_destination();
				std::string interface();
				void set_interface(std::string interface);
				bool has_interface();
				std::string member();
				void set_member(std::string member);
				bool has_member();
				std::string path();
				void set_path(std::string path);
				bool has_path();

				size_t num_args();

				template<typename T>
				void append_argument(T arg) {

					if(typeid(arg) == typeid(int))
						;
					else if(typeid(arg) == typeid(std::string))
						;
					else
						throw;


					//append_argument<T>(arg);
					//append_argument<T>::append_argument(this, arg);
//					std::cout << "append generic" << std::endl;
				}



				// void append_argument(int arg) {
				// 	std::cout << "append int" << std::endl;
				// }

				~Message();

			private:
				DBusMessage* _message;
				int _type;

				enum arg_type {
					type_string = 0,
					type_int
				};

				struct argument {
					arg_type type;
					union data {
						std::string string_data;
						int int_data;
					};
				};

				std::vector<argument> _arguments;

				friend class Connection;
			};

			// template<> void Message::append_argument(std::string arg);
			// template<> void Message::append_argument(int arg);

			// template<>
			// void Message::append_argument(std::string arg) {
			// 	std::cout << "append string" << std::endl;
			// }


			// template<>
			// void Message::append_argument(int arg) {
			// 	std::cout << "append int" << std::endl;
			// }

		}
	}
}

#endif