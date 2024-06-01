#include "link.h"
#include "node.h"

void Link::connect(const Node *node, Packet *packet) const
{
    if (node == nodeA_ || node == nodeB_)
    {
        // 다음 Node에 Packet 전달.
        std::cout << "Link: forwarding packet from node #" << node->id()
                  << ", to node #" << other(node)->id() << std::endl;
        other(node)->receive(packet);
    }
}