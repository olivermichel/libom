//
//  Olli's C++ Library
//  net/agent.cc
//  (c) 2012 Oliver Michel
//

#include "agent.h"

om::net::Agent::Agent() 
  : _interfaces(new std::map<int, IOInterface*>) {}

om::net::Agent::Agent(const om::net::Agent& copy_from) 
  : _interfaces(copy_from._interfaces) {}

om::net::Agent& om::net::Agent::operator=(const om::net::Agent& copy_from) {

  _interfaces = copy_from._interfaces;
  return *this;
}

std::map<int, om::net::IOInterface*>* om::net::Agent::interfaces() {

  return _interfaces;
}

void om::net::Agent::add_interface(om::net::IOInterface* iface)
   throw(std::logic_error) {

  if(!_interfaces->insert(std::make_pair(iface->fd(), iface)).second)
    throw std::logic_error("device is already added to this agent");
}

void om::net::Agent::run() {

}

om::net::Agent::~Agent() {

  delete _interfaces;
}
