#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H

#include "host.h"
#include "service.h"
#include "simulator.h"

#define PACKET_SIZE 512

class BulkSendService : Service
{
  friend class BulkSendServiceInstaller;

private:
  // 목적지 주소
  Address destAddress_;
  // 목적지 포트
  short destPort_;

  double delay_;
  double nowTime_;
  double stopTime_;

  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0)
      : Service(host, 0), destAddress_(destAddress), destPort_(destPort),
        delay_(delay), nowTime_(startTime), stopTime_(stopTime) {}
public:
  ~BulkSendService() = default;
  std::string name() override { return "BulkSendService"; };

  void send();
  void listener(Packet *packet);
};

#endif