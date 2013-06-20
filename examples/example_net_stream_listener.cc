//
//  Olli's C++ Library
//  examples/example_net_stream_listener.cc
//  (c) 2013 Oliver Michel
//

#include <iostream>
#include <set>
#include <string>
#include <typeinfo> 

#include <om/net/agent.h>
#include <om/net/net.h>
#include <om/net/stream_connection.h>
#include <om/net/stream_listener.h>

class ListeningExampleAgent : public om::net::Agent {

public:

  void device_ready(timeval* timestamp, om::net::IOInterface* iface) {


    if(typeid(*iface) == typeid(om::net::StreamListener)) {

      om::net::StreamListener* listener = 0;
      om::net::StreamConnection* connection = 0;
      om::net::tp_addr remote;

      std::cout << "new connection:" << std::endl;

      // cast interface to StreamListener object
      listener = dynamic_cast<om::net::StreamListener*>(iface);

      // accept new incoming connection and write remote addr into remote
      int new_fd = listener->accept(&remote);

      connection = new om::net::StreamConnection(new_fd, remote);
      this->add_interface(connection);

      std::cout << "   " << new_fd << " - " << remote.addr.to_string() << ":" 
        << remote.port << std::endl;

    } else if(typeid(*iface) == typeid(om::net::StreamConnection)) {



    }

  }
}; 


int main(int argc, char const *argv[]) {

  // configure wildcard address and tcp port to listen on
  om::net::tp_addr endpoint("0.0.0.0", om::net::tp_proto_tcp, 42742);

  // pass pointer to agent to new listener
  om::net::StreamListener* listener = new om::net::StreamListener(endpoint);

  // initiate the agent
  ListeningExampleAgent* a = new ListeningExampleAgent;

  // add the listener
  a->add_interface(listener);

  // start up the agent
  a->run();

  return 0;
}
