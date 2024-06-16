#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "object.h"
#include "packet.h"
#include <vector>

class Node : public Object
{
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;

protected:
  // 접근 가능한 link list
  std::vector<Link *> accessableLink;

public:
  std::string name() override { return "Node"; };

  Node() : id_(nextId_++) {}
  int id() const { return id_; }

  // 발신
  virtual void send(Packet *packet) = 0;

  // 수신
  virtual void receive(Packet *packet) = 0;
  // accessableLink에 접근할 수 있는 공용 접근자
  const std::vector<Link *> &getAccessableLink() const
  {
    return accessableLink;
  }
};

#endif