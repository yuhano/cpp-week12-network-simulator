#ifndef LINK_H
#define LINK_H

#include "object.h"
#include "packet.h"
#include <cstdlib>
#include <iostream>

class Node;

class Link : public Object
{
  friend class LinkInstaller;

private:
  Link(Node *nodeA, Node *nodeB, double delay = 0.0)
      : nodeA_(nodeA), nodeB_(nodeB), delay_(delay) {}

  Node *nodeA_;
  Node *nodeB_;
  double delay_;

public:
  double delay() { return delay_; }

  Node *nodeA() { return nodeA_; }

  Node *nodeB() { return nodeB_; }

  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  Node *other(const Node *node) const
  {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }

  double getDelay() { return delay_; }
  
  std::string name() override { return "Link"; };

  // Link의 데이터를 보내는 곳의 정보와 패킷 정보를 입력하면 반대편에 Packet을 전송
  void connect(const Node *node, Packet *packet) const;
};

#endif