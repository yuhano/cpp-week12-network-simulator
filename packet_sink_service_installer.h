#ifndef PACKET_SINK_SERVICE_INSTALLER_H
#define PACKET_SINK_SERVICE_INSTALLER_H

#include "address.h"
#include "packet_sink_service.h"
#include "service_installer.h"

class PacketSinkServiceInstaller : public ServiceInstaller
{
public:
  PacketSinkService *install(Host *host, short port)
  {
    // 서비스 객체 생성 및 host 내 서비스 리스트에 설치.
    PacketSinkService *newPacketSinkService = new PacketSinkService(host, port);
    ServiceInstaller::install(host, newPacketSinkService);

    // 새로 생성한 객체 반환
    return newPacketSinkService;
  }
};

#endif