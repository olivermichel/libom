//
//  Olli's C++ Library
//  examples/example_net_stream_client.cc
//  (c) 2013 Oliver Michel
//

#include <iostream>
#include <set>
#include <string>

#include <netinet/in.h>

#include <om/net/net.h>
#include <om/net/stream_client.h>

int main(int argc, char const *argv[]) {

  // open a connection to port 42742 at 192.168.56.2
  om::net::tp_addr server("192.168.56.2", om::net::tp_proto_tcp, 42742);

  om::net::StreamClient* sock = new om::net::StreamClient(server);

  const char* msg = "hello";
  sock->send((const unsigned char*) msg, 6);

  sock->close();
  delete sock;

  return 0;
}
