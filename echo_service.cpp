#include "echo_service.h"

void EchoService::listener(Packet *packet)
{
  // 수신 성공 메시지
  std::string tmpMsg = "received \"" + packet->dataString() + "\" from " + packet->srcAddress().toString() + ":" + std::to_string(packet->srcPort()) + ", send reply with same data";
  log(tmpMsg);

  // 반환을 위해, 목적지 정보와 출발지 정보를 변경하여 새로운 패킷 생성
  Packet *newPacket = new Packet(packet->destAddress(), packet->srcAddress(), packet->destPort(), packet->srcPort(), packet->data());

  // 기존 패킷 삭제
  delete packet;

  // 새로운 패킷 보내기
  host_->send(newPacket);
}