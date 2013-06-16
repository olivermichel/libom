//
//  Olli's C++ Library
//  examples/example_net_stream_listener.cc
//  (c) 2013 Oliver Michel
//

#include <iostream>
#include <set>
#include <string>

#include <typeinfo> 

#include <om/net/net.h>
#include <om/net/agent.h>
#include <om/net/stream_listener.h>

class ListeningExampleAgent : public om::net::Agent {

public:

  void device_ready(timeval* timestamp, om::net::IOInterface* iface) {

    if(typeid(*iface) == typeid(om::net::StreamListener)) {

      // new connection

    } // else if(typeid(*iface) == typeid(om::net::StreamConnection))

  }
}; 



int main(int argc, char const *argv[]) {

  ListeningExampleAgent* a = new ListeningExampleAgent;

  // configure wildcard address and tcp port to listen on
  om::net::tp_addr endpoint("0.0.0.0", om::net::tp_proto_tcp, 42742);

  // pass pointer to agent to new listener
  om::net::StreamListener* listener = new om::net::StreamListener(endpoint, a);

  // add the listener
  a->add_interface(listener);

  // start up the agent
  a->run();

  return 0;
}
