CC = g++
CFLAGS = -g -Wall -Werror -std=c++11

# 기본 목표
all: first.exe second.exe third.exe forth.exe fifth.exe sixth.exe

# 오브젝트 파일 생성 규칙
first.o: scenarios/first.cpp
	$(CC) $(CFLAGS) -c scenarios/first.cpp -o first.o

second.o: scenarios/second.cpp
	$(CC) $(CFLAGS) -c scenarios/second.cpp -o second.o

third.o: scenarios/third.cpp
	$(CC) $(CFLAGS) -c scenarios/third.cpp -o third.o

forth.o: scenarios/forth.cpp
	$(CC) $(CFLAGS) -c scenarios/forth.cpp -o forth.o

fifth.o: scenarios/fifth.cpp
	$(CC) $(CFLAGS) -c scenarios/fifth.cpp -o fifth.o

sixth.o: scenarios/sixth.cpp
	$(CC) $(CFLAGS) -c scenarios/sixth.cpp -o sixth.o

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

bulk_send_service.o: bulk_send_service.cpp
	$(CC) $(CFLAGS) -c bulk_send_service.cpp -o bulk_send_service.o

bulk_send_service_installer.o: bulk_send_service_installer.cpp
	$(CC) $(CFLAGS) -c bulk_send_service_installer.cpp -o bulk_send_service_installer.o

# auto_router.o: auto_router.cpp
# 	$(CC) $(CFLAGS) -c auto_router.cpp -o auto_router.o

# ------------- linking ------------------
OBJ = object.o echo_service.o echo_service_installer.o host.o link.o link_installer.o manual_router.o message_service.o message_service_installer.o router.o service_installer.o node.o simulator.o bulk_send_service.o bulk_send_service_installer.o 

# 실행 파일 생성 규칙
first.exe: first.o $(OBJ)
	$(CC) $(CFLAGS) -o first.exe first.o $(OBJ)

second.exe: second.o $(OBJ)
	$(CC) $(CFLAGS) -o second.exe second.o $(OBJ)

third.exe: third.o $(OBJ)
	$(CC) $(CFLAGS) -o third.exe third.o $(OBJ)

forth.exe: forth.o $(OBJ)
	$(CC) $(CFLAGS) -o forth.exe forth.o $(OBJ)

fifth.exe: fifth.o $(OBJ)
	$(CC) $(CFLAGS) -o fifth.exe fifth.o $(OBJ)

sixth.exe: sixth.o $(OBJ)
	$(CC) $(CFLAGS) -o sixth.exe sixth.o $(OBJ)

# 청소 규칙
# rm -f *.o first.exe second.exe
clean:
	del /F *.o first.exe second.exe third.exe forth.exe fifth.exe sixth.exe



# 기본 목표 설정
.PHONY: all clean first second third forth

# first 목표를 first.exe로 매핑
first: first.exe

# second 목표를 second.exe로 매핑
second: second.exe

# third 목표를 third.exe로 매핑
third: third.exe

# forth 목표를 forth.exe로 매핑
forth: forth.exe

# fifth 목표를 fifth.exe로 매핑
fifth: fifth.exe

# sixth 목표를 sixth.exe로 매핑
sixth: sixth.exe