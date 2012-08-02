//
//  Olli's C++ Library
//  test_net_main.cc
//  (c) 2012 Oliver Michel
//

#include <iostream>
#include <typeinfo>
#include <iomanip>
#include <cstring>

#include <netinet/ip.h>
#include <signal.h>

#include "net/net.h"

#include "net/datagram_socket.h"
#include "net/raw_socket.h"
#include "net/agent.h"
#include "net/io_interface.h"
#include "net/raw_socket.h"


// class TestAgent : public om::net::Agent {

//   void device_ready(timeval* timestamp, om::net::IOInterface* iface) {

//     if(iface->type() == om::net::IOInterface::iface_type_sock_dgram)
//       std::cout << "received from a datagram socket" << std::endl;

//   }
  
//   void timeout_trigger(timeval* timestamp, timeval* timeout) {
//     std::cout << "timestamp: " << timestamp->tv_sec << ":" << timestamp->tv_usec << std::endl;
//     std::cout << "timeout: " << timeout->tv_sec << ":"  << timeout->tv_usec << std::endl;
//   }
// };

void signal_handler(int sig) {

  std::cout << "test_net: received SIGINT " << sig << std::endl;
  exit(1);
}

int main(int argc, char const *argv[]) {
  
  signal(SIGINT, signal_handler);

  // om::net::ip_endpoint e1(om::net::tp_proto_udp, "0.0.0.0", 12031);
  // om::net::ip_endpoint e2(om::net::tp_proto_udp, "0.0.0.0", 12032);
  // om::net::ip_endpoint e3(om::net::tp_proto_udp, "0.0.0.0", 12033);

  // TestAgent* a = new TestAgent();
  // om::net::DatagramSocket* s1 = new om::net::DatagramSocket(e1);
  // om::net::DatagramSocket* s2 = new om::net::DatagramSocket(e2);
  // om::net::DatagramSocket* s3 = new om::net::DatagramSocket(e3);

  // a->add_interface(s1);
  // a->add_interface(s2);
  // a->add_interface(s3);

  //a->set_timeout_mode(om::net::Agent::timeout_mode_manual);
  //a->set_manual_timeout(0.5);

  // a->set_timeout_mode(om::net::Agent::timeout_mode_uniform);
  // a->set_uniform_lower(0.5);
  // a->set_uniform_upper(1.0);

  // a->set_timeout_mode(om::net::Agent::timeout_mode_exponential);
  // a->set_exponential_lambda(1.0);

  // a->run();


  //struct iphdr* hdr = new iphdr;

  // struct iphdr hdr;
  // //char pl[] = "hello";
  
  
  // std::string pl("hello");

  // //char dgram[1500] = {0};

  // size_t hdr_len = sizeof(struct iphdr);
  // size_t pl_len = pl.size();
  // size_t dgram_len = hdr_len + pl_len;

  // std::string dgram(dgram_len,0);
  // std::cout << "size to be allocated: " << hdr_len << "+" << pl_len << "=" << dgram_len << std::endl;

  // struct sockaddr_in dst_addr;
  // dst_addr.sin_family = AF_INET;
  // dst_addr.sin_addr.s_addr = inet_addr("192.168.57.11");

  // hdr.ihl = hdr_len/4;
  // hdr.version = 4;
  // hdr.tos = 0;
  // hdr.tot_len = dgram_len;
  // hdr.id = htons(rand());
  // hdr.frag_off = 0;
  // hdr.ttl = 255;
  // hdr.protocol = IPPROTO_RAW;
  // hdr.check = 0;
  // hdr.saddr = inet_addr("192.168.57.3");
  // hdr.daddr = inet_addr("192.168.57.11");

  // dgram.append(hdr);
  // //dgram.assign(pl, hdr_len, pl_len);

  // // std::memcpy(dgram, &hdr, hdr_len);
  // // std::memcpy(dgram + hdr_len, pl, pl_len);

  

  // for(size_t i = 0; i < dgram_len; i++)
  //   std::cout << std::setw(2) << i << ":0x" << std::setw(2) << std::ios::hex << (int)dgram[i] << " ";
  // std::cout << std::dec << std::endl;



  // // memcpy(datagram, header, sizeof(struct iphdr));
  // // memcpy(datagram + sizeof(struct iphdr), message, sizeof(message));
  
  char packet[] = {0x01, 0x02, 0x03, 0x04, 0x05, 'h', 'e', 'l', 'l', 'o'};

  om::net::RawSocket rs;
  int b = rs.send_raw("192.168.57.11", packet, 10);

  std::cout << "sent " << b << " bytes" << std::endl;

  // delete hdr;
  // delete[] dgram;

  return 0;
}
