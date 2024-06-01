# 코드에서 사용된 문법 정리

## Vector

### 생성 및 push
``` c++
#include <vector>

  std::vector<ManualRouter *> routers;
  for (int i = 0; i < 4; i++) {
    routers.push_back(new ManualRouter());
  }
```

## 상속

### 소멸자 
Node a = Host(); 처럼 선언된 경우, a을 지우면 부모인 Node의 소멸자면 호출이 된다.

이를 방지하기 위해 자식에서도 가상의 소멸자를 만들어주어야한다.(자식을 삭제하기 위하여)

``` c++
class Host : public Node
{
public:
  // host 소멸자 (Node와 Host을 삭제하기 위한)
  virtual ~Host() {}
};
```

### 순수 가상 함수
아래와 같이 virtual void foo() = 0; 로 선언이 되어 있는 것을 순수한 가상 함수라고 한다.

상속받은 자식 클래스는 무조건 해당 순수 가상 함수를 override 시켜줘야 한다.


``` c++
class Node
{
  // 수신
  // 순수한 가상 함수 / 추상 함수
  virtual void receive(Packet *packet) = 0;
};

class Host : public Node
{
  // 링크를 통해 상대 host로부터 패킷을 받는다.
  void receive(Packet *packet);
};

void Host::receive(Packet *packet)
{
    ...
}
```

### friend
다른 클래스트에서 해당 클래스를 수정할 수 있도록 한다.
``` c++
class Node
{
  friend class LinkInstaller;
}

class LinkInstaller {
public:
  // 노드 a, b 사이에 링크를 설치하고 반환한다.
  Link *install(Node *a, Node *b);
};
```


