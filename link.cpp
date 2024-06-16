#include "link.h"
#include "node.h"

void Link::connect(const Node *node, Packet *packet) const
{
    // 다음 Node에 Packet 전달.
    std::string tmpMsg = "packet in: " + packet->toString() + " from " + const_cast<Node *>((node))->toString()+" " ;
    const_cast<Link *>(this)->log(tmpMsg);

    Node *otherNode = other(node);
    Simulator::schedule(delay_,
                        [this, otherNode, packet]()
                        {
                            std::string tmpMsg = "packet out: " + packet->toString() + " to " + const_cast<Node *>(otherNode)->toString()+"";
                            const_cast<Link *>(this)->log(tmpMsg);
                            otherNode->receive(packet);
                        });
}
