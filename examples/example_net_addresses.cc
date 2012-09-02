//
//  Olli's C++ Library
//  examples/ex_tun_device.cc
//  (c) 2012 Oliver Michel
//

#include <iostream>
#include <string>
#include <vector>

#include <netinet/in.h>

#include <om/tools/string.h>
#include <om/net/net.h>

int main(int argc, char const *argv[]) {

  // construct IP addresses using simple char* literals
  om::net::nw_addr addr1 = "255.255.255.255";
  om::net::nw_addr addr2 = "121.19.4.22";

  // a full L4 socket specification is given by the 3-tuple ip, protocol, port
  om::net::tp_addr e1 = om::net::tp_addr(addr1, om::net::tp_proto_tcp, 80);
  om::net::tp_addr e2 = om::net::tp_addr(addr2, om::net::tp_proto_tcp, 80);

  // pairs can be built on both the network and transport layer
  om::net::nw_pair p1(addr1, addr2);
  om::net::tp_pair p2(e1, e2);

  // when directly setting up connection-pairs, shorter statements are possible:
  om::net::tp_pair p3(
    om::net::tp_addr("192.168.0.1", om::net::tp_proto_udp, 8283),
    om::net::tp_addr("192.168.0.2", om::net::tp_proto_udp, 8283)
  );

  om::net::nw_addr addr3 = "0.0.0.0";

  // check if all bytes are set to zero
  if(addr3.is_empty())
    std::cout << "0.0.0.0 is empty" << std::endl;


  // explicitely call conversion functions to c++ and c strings
  std::cout << addr2.to_string() << std::endl;
  std::cout << addr3.to_cstring() << std::endl;

  // translate between transport layer addresses and sockaddr_in structs 
  sockaddr_in i;

  om::net::sockaddr_from_tp_addr(&e1, &i);
  om::net::sockaddr_from_tp_addr(e1, &i);

  om::net::tp_addr e3;
  om::net::tp_addr_from_sockaddr(&i, &e3);

  return 0;
}
