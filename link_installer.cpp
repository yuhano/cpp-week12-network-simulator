#include "link_installer.h"

// 노드 a, b 사이에 링크를 설치하고 반환한다.
Link *LinkInstaller::install(Node *a, Node *b, double delay)
{
    // 새로운 링크 생성 및 각 Node의 연결 링크에 저장
    Link *newLink = new Link(a,b);
    a->accessableLink.push_back(newLink);
    b->accessableLink.push_back(newLink);

    // 새롭게 생성한 링크에 저장
    return newLink;
}