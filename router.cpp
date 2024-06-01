#include "router.h"

void Router::send(Packet *packet)
{
    // 전송 가능한 링크 중 routingtable에 목적지가 있는지 검사.
    Link *sendLink = nullptr;
    for (RoutingEntry i : routingTable_)
    {
        if (i.destination == packet->destAddress())
        {
            sendLink = i.nextLink;
            break;
        }
    }

    if (sendLink) // 라우팅 테이블에 값이 있어 전송이 가능한 경우
    {
        std::cout
            << "Router #" << id()
            << ": forwarding packet (from: " << packet->srcAddress().toString()
            << ", to: " << packet->destAddress().toString()
            << ", " << packet->data().size() << " bytes)" << std::endl;

        sendLink->connect(this, packet);
    }
    else // 라우팅 테이블에 값이 없어 전송이 불가능한 경우
    {
        std::cout
            << "Router #" << id()
            << ": no route for packet (from: " << packet->srcAddress().toString()
            << ", to: " << packet->destAddress().toString()
            << ", " << packet->data().size() << " bytes)" << std::endl;
        delete packet;
    }
}

void Router::receive(Packet *packet)
{
    send(packet);
}