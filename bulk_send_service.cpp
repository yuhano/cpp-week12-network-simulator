#include "bulk_send_service.h"

void BulkSendService::listener(Packet *packet)
{
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
    nowTime_ = nowTime_ + delay_;
    Simulator::schedule(
        nowTime_ - Simulator::now(), [this]()
        { this->send(); });
}
