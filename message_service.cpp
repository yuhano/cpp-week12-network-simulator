#include "message_service.h"

void MessageService::send(std::string message)
{
    // 매시지 패킷 생성
    Packet *sendPacket_ = new Packet(host_->address(), destAddress_, srcPort_, destPort_, message);

    // host에게 패킷 보내기
    host_->send(sendPacket_);
}

void MessageService::listener(Packet *packet)
{
    // 메시지 수신 완료
    std::string tmpMsg = "received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort());
    log(tmpMsg);

    delete packet;
}
