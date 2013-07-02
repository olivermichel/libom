//
//  Olli's C++ Library
//  net/inotify_handler.h
//  (c) 2013 Oliver Michel <oliver dot michel at editum dot de>
//  
//  This class abstracts a file descriptor handle returned by a inotify_init()
//  call. multiple watches may be added to this handler.
//

#ifndef OM_NET_INOTIFY_HANDLER_H
#define OM_NET_INOTIFY_HANDLER_H

#include <om/net/net.h>
#include <om/net/io_interface.h>

namespace om {
  namespace net {

    class INotifyHandler : public om::net::IOInterface {

    public:

      explicit INotifyHandler()
        throw(std::runtime_error);
      explicit INotifyHandler(const om::net::INotifyHandler& copy_from);  
      INotifyHandler& operator=(INotifyHandler& copy_from);

      virtual ~INotifyHandler();
    };
  }
}

#endif
