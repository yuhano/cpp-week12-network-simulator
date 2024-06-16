#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service
{
private:
  friend class PacketSinkServiceInstaller;

  PacketSinkService(Host *host, short port) : Service(host, port){};

  int totalPacketSize_ = 0;

public:
  void listener(Packet *packet)
  {
    // 메시지 데이터 크기 더하기
    totalPacketSize_ += packet-> data().size();

    // 메시지 수신 완료
    std::string tmpMsg = "received total " + std::to_string(totalPacketSize_) + " bytes";
    log(tmpMsg);

    delete packet;
  }
  std::string name() override { return "PacketSinkService"; }
};

#endif