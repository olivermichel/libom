//
//  Olli's C++ Library
//  net/inotify_handler.cc
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//

#include <om/net/inotify_handler.h>

om::net::INotifyHandler::INotifyHandler()
  throw(std::runtime_error)
  : om::net::IOInterface(om::net::IOInterface::iface_type_inotify_handler) {}

om::net::INotifyHandler::INotifyHandler(const om::net::INotifyHandler& copy_from)
  : om::net::IOInterface(copy_from) {}

om::net::INotifyHandler& 
  om::net::INotifyHandler::operator=(INotifyHandler& copy_from) {

  om::net::IOInterface::operator=(copy_from);
  return *this;
}

om::net::INotifyHandler::~INotifyHandler() {}
