//
//  Olli's C++ Library
//  examples/example_stream_socket.cc
//  (c) 2012 Oliver Michel
//

#include <iostream>
#include <set>
#include <string>

#include <netinet/in.h>

#include <om/net/net.h>
#include <om/net/stream_socket.h>
#include <om/net/agent.h>

class ExampleAgent : public om::net::Agent {

  void device_ready(timeval* timestamp, om::net::IOInterface* iface) {

    std::cout << "device ready " << std::endl;

    if(iface->type() == om::net::IOInterface::iface_type_sock_stream)
      std::cout << " stream socket " << std::endl;

    unsigned char rx_buf[1500] = {0};
    int rx_bytes = 0;

    om::net::StreamSocket* sock =
      dynamic_cast<om::net::StreamSocket*>(iface);

    om::net::tp_addr sender;

//    rx_bytes = sock->receive(&sender, rx_buf, sizeof(rx_buf));

    std::cout << "receive " << rx_bytes << " Bytes" << std::endl;
  }
};


int main(int argc, char const *argv[]) {


  // bind to any source ip address (0.0.0.0)
  om::net::tp_addr addr("0.0.0.0", om::net::tp_proto_tcp, 42742);

  om::net::StreamSocket* sock = new om::net::StreamSocket(addr);


  // allocate previously defined agent
  ExampleAgent* a = new ExampleAgent;

  // add any object that inherits from om::net::IOInterface to the agent
  a->add_interface(sock);
  
  // fire up the agent (blocking)
  a->run();

  // close and delete socket
  sock->close();
  delete sock;

  return 0;
}
