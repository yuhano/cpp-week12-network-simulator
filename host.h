#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>

class Host : public Node
{
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

  std::string name() override { return "Host"; };

public:
  // host 소멸자 (Node와 Host을 삭제하기 위한)
  ~Host()
  {
    for (auto &i : services_)
    {
      if (i != nullptr)
      {
        delete i;
        i = nullptr;
      }
    }
  }

  Address address() { return address_; }
  Host(Address address) : address_(address) {}

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize();

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet);

  // 링크를 통해 상대 host로부터 패킷을 받는다.
  void receive(Packet *packet);
};

#endif