//
//  Olli's C++ Library
//  net/agent.cc
//  (c) 2012 Oliver Michel
//

#include "agent.h"

om::net::Agent::Agent() 
  : _interfaces(new std::map<int, om::net::IOInterface*>), 
    _timeout_mode(om::net::Agent::timeout_mode_none),
    _manual_timeout(0), _uniform_lower(0), _uniform_upper(0),
    _exponential_lambda(0) {}

om::net::Agent::Agent(const om::net::Agent& copy_from) 
  : _interfaces(copy_from._interfaces), 
    _timeout_mode(copy_from._timeout_mode),
    _manual_timeout(copy_from._manual_timeout),
    _uniform_lower(copy_from._uniform_lower),
    _uniform_upper(copy_from._uniform_upper),
    _exponential_lambda(copy_from._exponential_lambda) {}

om::net::Agent& om::net::Agent::operator=(const om::net::Agent& copy_from) {

  _interfaces = copy_from._interfaces;
  _timeout_mode = copy_from._timeout_mode;
  _manual_timeout = copy_from._manual_timeout;
  _uniform_lower = copy_from._uniform_lower;
  _uniform_upper = copy_from._uniform_upper;
  _exponential_lambda = copy_from._exponential_lambda;

  return *this;
}

std::map<int, om::net::IOInterface*>* om::net::Agent::interfaces() const {

  return _interfaces;
}

void om::net::Agent::set_timeout_mode(om::net::Agent::timeout_mode_t t) {

  _timeout_mode = t;
}

om::net::Agent::timeout_mode_t om::net::Agent::timeout_mode() const {

  return _timeout_mode;
}

void om::net::Agent::set_manual_timeout(double t) {

  _manual_timeout = t;
}

double om::net::Agent::manual_timeout() {

  return _manual_timeout;
}

void om::net::Agent::set_uniform_lower(double l) {

  _uniform_lower = l;
}

double om::net::Agent::uniform_lower() {

  return _uniform_lower;
}

void om::net::Agent::set_uniform_upper(double u) {

  _uniform_upper = u;
}

double om::net::Agent::uniform_upper() {

  return _uniform_upper;
}

void om::net::Agent::set_exponential_lambda(double l) {

  _exponential_lambda = l;
}

double om::net::Agent::exponential_lambda() {

  return _exponential_lambda;
}

void om::net::Agent::add_interface(om::net::IOInterface* iface)
   throw(std::logic_error) {

  if(!_interfaces->insert(std::make_pair(iface->fd(), iface)).second)
    throw std::logic_error("device is already added to this agent");
}

void om::net::Agent::timeout_triggered() {}

void om::net::Agent::run() {

  // ...
}

om::net::Agent::~Agent() {

  delete _interfaces;
}
