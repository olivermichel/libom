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
#include <iostream>

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

				void append_int32(int32_t arg);
				int32_t get_int32(size_t pos)
					throw(std::logic_error, std::invalid_argument, std::out_of_range);

				void append_string(std::string arg);
				std::string get_string(size_t pos)
					throw(std::logic_error, std::invalid_argument, std::out_of_range);

/*
				template<typename T>
				void append_argument(T arg) throw(std::invalid_argument) {
					if(typeid(arg) == typeid(int))
						_append_int(&arg);
					else if(typeid(arg) == typeid(std::string))
						_append_string(&arg);
					else
						throw std::invalid_argument("om::ipc::dbus::Message: " +
							std::string("argument type not supported"));
				}

				template<typename T>
				void get_argument(size_t pos, T* dst) throw(std::logic_error)
				{
					if(typeid(T) == typeid(int))
						_get_int(pos, (int*) dst);
					else if(typeid(T) == typeid(std::string))
						_get_string(pos, (std::string*) dst);
					else
						throw std::invalid_argument("om::ipc::dbus::Message: " +
							std::string("argument type not supported"));
				}
*/
				std::string description();

				~Message();

			private:

				DBusMessage* _message;
				int _type;
/*
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
*/
/*
				void _append_string(void* arg);
				void _append_int(void* arg);

				void _get_string(size_t pos, std::string* dst);
				void _get_int(size_t pos, int* dst);
*/

				void _init_iter(DBusMessageIter* iter)
					throw(std::logic_error);

				void _advance_iter(DBusMessageIter* iter, size_t k)
					throw(std::out_of_range);

				friend class Connection;
//				friend std::ostream& operator<<(std::ostream& os, const om::ipc::dbus::Message& msg);
			};

		}
	}
}

#endif