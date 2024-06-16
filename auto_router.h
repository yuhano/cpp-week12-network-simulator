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
#include <unordered_map>
#include <unordered_set>
class AutoRouter : public Router
{
public:
    std::string name() override { return "AutoRouter"; };
    void calculate(const std::vector<Node *> &nodes,
                   const std::vector<Link *> &links)
    {
        // 각 노드에 대한 라우팅 테이블을 초기화합니다.
        routingTable_.clear();

        // 모든 호스트 노드에 대해 루프를 돌며 라우팅 테이블을 계산합니다.
        for (Node *node : nodes)
        {
            if (Host *host = dynamic_cast<Host *>(node))
            {
                Address destination = host->address();
                std::unordered_map<Node *, double> minDistance;
                std::unordered_map<Node *, Link *> previousLink;

                // 모든 노드의 거리를 무한대로 초기화합니다.
                for (Node *n : nodes)
                {
                    minDistance[n] = std::numeric_limits<double>::infinity();
                }

                // 시작 노드의 거리를 0으로 설정합니다.
                minDistance[this] = 0;

                // 우선순위 큐를 사용하여 최단 거리 노드를 찾습니다.
                using NodeDistPair = std::pair<double, Node *>;
                std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<NodeDistPair>> pq;
                pq.push({0, this});

                while (!pq.empty())
                {
                    double currentDist = pq.top().first;
                    Node *currentNode = pq.top().second;
                    pq.pop();

                    if (currentDist > minDistance[currentNode])
                    {
                        continue;
                    }

                    // 현재 노드에서 연결된 링크를 통해 이웃 노드로 이동합니다.
                    for (Link *link : currentNode->getAccessableLink())
                    {
                        Node *neighbor = link->other(currentNode);
                        double newDist = currentDist + link->getDelay();

                        if (newDist < minDistance[neighbor])
                        {
                            minDistance[neighbor] = newDist;
                            previousLink[neighbor] = link;
                            pq.push({newDist, neighbor});
                        }
                    }
                }

                // 목적지 호스트까지의 경로를 라우팅 테이블에 추가합니다.
                if (previousLink.find(host) != previousLink.end())
                {
                    Link *nextLink = previousLink[host];
                    Node *prevNode = host;

                    // 목적지 호스트로 가는 경로 중 첫 번째 링크를 찾습니다.
                    while (previousLink.find(prevNode) != previousLink.end() && previousLink[prevNode] != nullptr)
                    {
                        nextLink = previousLink[prevNode];
                        prevNode = nextLink->other(prevNode);
                    }

                    // 라우팅 엔트리를 라우팅 테이블에 추가합니다.
                    routingTable_.emplace_back(destination, nextLink);
                }
            }
        }
    }
};

#endif