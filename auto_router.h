#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <iostream>

class AutoRouter : public Router
{
public:
  void calculate(const std::vector<Node *> &nodes,
                 const std::vector<Link *> &links)
  {
    // 전체 노드와 링크 정보를 통해
    // 모든 호스트로 전달될 수 있는 라우팅 테이블을 구성한다
    // TODO: 구현
    auto newDijkstraTable = generateDijkstraTable(nodes, links);

    int thisIndex = findNode(nodes, this);

    distances = runDijkstra(newDijkstraTable, thisIndex);
  }

private:
  // DijkstraTable 계산 결과
  std::vector<double> distances;

  // 특정 포인터 값을 배열에서 찾는 함수
  int findNode(const std::vector<Node *> &nodes, Node *target);

  // DijkstraTable 생성 함수
  std::vector<std::vector<double>> generateDijkstraTable(const std::vector<Node *> &nodes, const std::vector<Link *> &links);

  // Dijkstra 거리 계산 결과 함수
  std::vector<double> AutoRouter::runDijkstra(const std::vector<std::vector<double>> &tableCost, int startNode);
};

#endif