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
        std::string tmpMsg = "forwarding packet: " + packet->toString() + " to " + sendLink->toString();
        log(tmpMsg);

        sendLink->connect(this, packet);
    }
    else // 라우팅 테이블에 값이 없어 전송이 불가능한 경우
    {

        std::string tmpMsg = "no route for packet: "+packet->toString();
        log(tmpMsg);
        delete packet;
    }
}

void Router::receive(Packet *packet)
{
    send(packet);
}