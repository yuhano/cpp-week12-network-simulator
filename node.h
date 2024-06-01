#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

class Node
{
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

protected:
  // 접근 가능한 link list
  std::vector<Link *> accessableLink;

public:
  Node() : id_(nextId_++) {}
  int id() const { return id_; }

  // 발신
  virtual void send(Packet *packet) = 0;

  // 수신
  virtual void receive(Packet *packet) = 0;
};

#endif