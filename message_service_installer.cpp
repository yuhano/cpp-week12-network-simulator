#include "message_service_installer.h"

// 호스트에 MessageService 설치한다.
MessageService *MessageServiceInstaller::install(Host *host)
{
    // 서비스 객체 생성 및 host 내 서비스 리스트에 설치.
    MessageService *newMessageService = new MessageService(host, destPort_, destAddress_, destPort_);
    ServiceInstaller::install(host, newMessageService);

    // 새로 생성한 객체 반환
    return newMessageService;
}
