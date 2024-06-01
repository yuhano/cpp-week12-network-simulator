#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry
{
public:
  Address destination;
  Link *nextLink;

  RoutingEntry(const Address &dest, Link *link) : destination(dest), nextLink(link) {}

  ~RoutingEntry()
  {
  }
};

class Router : public Node
{
protected:
  std::vector<RoutingEntry> routingTable_;

public:
  // 발신
  void send(Packet *packet);

  // 수신
  void receive(Packet *packet);
};

#endif