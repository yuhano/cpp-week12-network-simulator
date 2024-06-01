#include "echo_service_installer.h"

// 호스트에 EchoService를 설치한다.
EchoService *EchoServiceInstaller::install(Host *host)
{
    // 서비스 객체 생성 및 host 내 서비스 리스트에 설치.
    EchoService *newEchoService = new EchoService(host, listenPort_);
    ServiceInstaller::install(host, newEchoService);

    // 새로 생성한 객체 반환
    return newEchoService;
}