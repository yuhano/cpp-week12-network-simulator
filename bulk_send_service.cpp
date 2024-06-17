#include "bulk_send_service.h"

void BulkSendService::listener(Packet *packet)
{
    // 수신 성공 메시지
    std::string tmpMsg = "received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()) + ", send reply with same data";
    log(tmpMsg);

    // 기존 패킷 삭제
    delete packet;
}

void BulkSendService::send()
{

    if (Simulator::now() >= stopTime_)
    {
        return;
    }
    log("sending data");
    // 더미 데이터 생성
    std::string message_(PACKET_SIZE, 'A');
    Packet *sendPacket_ = new Packet(host_->address(), destAddress_, srcPort_, destPort_, message_);
    host_->send(sendPacket_);

    // bulk send의 단독적인 delay 설정을 위하여
    Simulator::schedule(
        delay_, [this]()
        { this->send(); });
}
