#include "service_installer.h"

// 자식 서비스는 공통적으로 해당 함수를 이용하여 host에 설치가 가능하다.
void ServiceInstaller::install(Host *host, Service *service)
{
    // host, service는 둘 다 ServiceInstaller을 friend로 두고 있기 때문에
    // private 변수에 접근이 가능하다.

    // host의 출발지 포트가 겹치지 않도록 조치
    service->srcPort_ = 1000 + host->services_.size();

    // host의 services 추가
    host->services_.push_back(service);
}
