#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"
#include "object.h"

class Host;

class Service : public Object {
  friend class ServiceInstaller;

protected:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  // 출발지 포트
  short srcPort_;

  Service(Host *host, int port) : host_(host), port_(port) {}


public:
  virtual ~Service() = default;

  // 서비스가 사용하는 포트
  short port() { return port_; }

  // 서비스 내에, host로부터 packet을 받는 함수
  virtual void listener(Packet *packet) = 0;

  std::string name() override { return "Service"; };

};

#endif