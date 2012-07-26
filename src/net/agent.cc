//
//  Olli's C++ Library
//  net/agent.cc
//  (c) 2012 Oliver Michel
//

#include "agent.h"

om::net::Agent::Agent() 
  : _interfaces(new std::map<int, IOInterface>) {}

om::net::Agent::Agent(const om::net::Agent& copy_from) 
  : _interfaces(copy_from._interfaces) {}

om::net::Agent& om::net::Agent::operator=(const om::net::Agent& copy_from) {

  return *this;
}

std::map<int, om::net::IOInterface>* om::net::Agent::interfaces() {

  return 0;
}

void om::net::Agent::add_interface(om::net::IOInterface* iface) {

}

void om::net::Agent::run() {

}

om::net::Agent::~Agent() {

}
