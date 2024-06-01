#include "host.h"

// 호스트와 설치된 서비스를 전부 초기화한다.
void Host::initialize()
{
}

// 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
void Host::send(Packet *packet)
{
    // 발신 시작 메시지
    std::cout << "Host #" << id()
              << ": sending packet (from: " << packet->srcAddress().toString()
              << ", to: " << packet->destAddress().toString()
              << ", " << packet->dataString().length() << " bytes)" << std::endl;

    // 패킷 보내기
    // host에 연결된 link가 없으면 연결 시도하지 않음.
    if (accessableLink.size() != 0)
    {
        if (!accessableLink.empty())
            accessableLink.front()->connect(this, packet);
    }
}

void Host::receive(Packet *packet)
{
    // packet이 도착하고자 하는 포트를 해당 호스트에서 사용하고 있는지 검사.
    Service *packetToService = nullptr;
    for (Service *i : services_)
    {
        if (i->port() == packet->destPort() || i->port() == packet->srcPort())
        {
            packetToService = i;
            break;
        }
    }

    
    if (packetToService) // packet 도착 포트를 사용하는 서비스가 있는 경우
    {
        std::cout << "Host #" << id()
                  << ": received packet, destination port: " << packet->destPort() << std::endl;
        packetToService->listener(packet);
    }
    else // 없는 경우
    {
        std::cout << "Host #" << id()
                  << ": no service for packet (from: " << packet->srcAddress().toString()
                  << ", to: " << packet->destAddress().toString()
                  << ", " << packet->data().size()
                  << " bytes)" << std::endl;
    }
}