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

#include <errno.h>
#include <sys/inotify.h>
#include <sys/types.h>
#include <unistd.h>

#include <om/net/io_interface.h>
#include <om/net/net.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )

namespace om {
  namespace net {

    class INotifyHandler : public om::net::IOInterface {

    public:

      explicit INotifyHandler()
        throw(std::runtime_error);
      explicit INotifyHandler(const om::net::INotifyHandler& copy_from);  
      INotifyHandler& operator=(INotifyHandler& copy_from);

      void add_watch(std::string pathname, uint32_t mask)
        throw(std::runtime_error);

      ssize_t read_event(char* buf, size_t len)
        throw(std::runtime_error);

      virtual ~INotifyHandler();
    };
  }
}

#endif
