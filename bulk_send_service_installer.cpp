#include "bulk_send_service_installer.h"

BulkSendService *BulkSendServiceInstaller::install(Host *host, Address destination, short destPort,
                                                   double delay, double startTime, double stopTime)
{
    // 서비스 객체 생성 및 host 내 서비스 리스트에 설치.
    BulkSendService *newBulkSendService = new BulkSendService(host, destination, destPort, delay, startTime, stopTime);
    ServiceInstaller::install(host, newBulkSendService);

    // 시작시점 기준 새로운 반복 서비스 등록
    Simulator::schedule(
        startTime, [newBulkSendService]()
        { newBulkSendService->send(); });

    // 새로 생성한 객체 반환
    return newBulkSendService;
}