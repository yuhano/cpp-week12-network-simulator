CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

# 기본 목표
all: first.exe second.exe

# 오브젝트 파일 생성 규칙
first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp -o first.o

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp -o second.o

object.o: object.cpp
	$(CC) $(CFLAGS) -c object.cpp -o object.o

echo_service.o: echo_service.cpp
	$(CC) $(CFLAGS) -c echo_service.cpp -o echo_service.o

echo_service_installer.o: echo_service_installer.cpp
	$(CC) $(CFLAGS) -c echo_service_installer.cpp -o echo_service_installer.o

host.o: host.cpp
	$(CC) $(CFLAGS) -c host.cpp -o host.o

link.o: link.cpp
	$(CC) $(CFLAGS) -c link.cpp -o link.o

link_installer.o: link_installer.cpp
	$(CC) $(CFLAGS) -c link_installer.cpp -o link_installer.o

manual_router.o: manual_router.cpp
	$(CC) $(CFLAGS) -c manual_router.cpp -o manual_router.o

message_service.o: message_service.cpp
	$(CC) $(CFLAGS) -c message_service.cpp -o message_service.o

message_service_installer.o: message_service_installer.cpp
	$(CC) $(CFLAGS) -c message_service_installer.cpp -o message_service_installer.o

router.o: router.cpp
	$(CC) $(CFLAGS) -c router.cpp -o router.o

service_installer.o: service_installer.cpp
	$(CC) $(CFLAGS) -c service_installer.cpp -o service_installer.o

node.o: node.cpp
	$(CC) $(CFLAGS) -c node.cpp -o node.o

simulator.o: simulator.cpp
	$(CC) $(CFLAGS) -c simulator.cpp -o simulator.o

# 실행 파일 생성 규칙
first.exe: first.o object.o echo_service.o echo_service_installer.o host.o link.o link_installer.o manual_router.o message_service.o message_service_installer.o router.o service_installer.o node.o simulator.o
	$(CC) $(CFLAGS) -o first.exe first.o object.o echo_service.o echo_service_installer.o host.o link.o link_installer.o manual_router.o message_service.o message_service_installer.o router.o service_installer.o node.o simulator.o

second.exe: second.o object.o echo_service.o echo_service_installer.o host.o link.o link_installer.o manual_router.o message_service.o message_service_installer.o router.o service_installer.o node.o simulator.o
	$(CC) $(CFLAGS) -o second.exe second.o object.o echo_service.o echo_service_installer.o host.o link.o link_installer.o manual_router.o message_service.o message_service_installer.o router.o service_installer.o node.o simulator.o

# 청소 규칙
# rm -f *.o first.exe second.exe
clean:
	del /F *.o first.exe second.exe

# 기본 목표 설정
.PHONY: all clean first second

# first 목표를 first.exe로 매핑
first: first.exe

# second 목표를 second.exe로 매핑
second: second.exe
