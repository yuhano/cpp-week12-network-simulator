#include "auto_router.h"

int AutoRouter::findNode(const std::vector<Node *> &nodes, Node *target)
{
    auto it = std::find(nodes.begin(), nodes.end(), target);
    if (it != nodes.end())
    {
        return std::distance(nodes.begin(), it); // 일치하는 인덱스 반환
    }
    return -1; // 노드를 찾지 못한 경우
}

std::vector<std::vector<double>> AutoRouter::generateDijkstraTable(const std::vector<Node *> &nodes, const std::vector<Link *> &links)
{
    std::vector<Node *> tableIndex;

    for (const auto &node : nodes)
    {

        tableIndex.push_back(node);
    }

    int nodeSize = tableIndex.size();
    std::vector<std::vector<double>> tableCost(nodeSize,
                                               std::vector<double>(nodeSize, std::numeric_limits<double>::infinity()));
    for (int i = 0; i < nodeSize; ++i)
    {
        tableCost[i][i] = 0;
    }

    for (const auto &link : links)
    {
        int nodeAIndex_ = findNode(tableIndex, link->nodeA());
        int nodeBIndex_ = findNode(tableIndex, link->nodeB());

        tableCost[nodeAIndex_][nodeBIndex_] = link->getDelay();
        tableCost[nodeBIndex_][nodeAIndex_] = link->getDelay();
    }

    return tableCost;
}

std::vector<double> AutoRouter::runDijkstra(const std::vector<std::vector<double>> &tableCost, int startNode)
{
    int n = tableCost.size();                                                  // 노드의 수를 가져옵니다.
    std::vector<double> distances(n, std::numeric_limits<double>::infinity()); // 모든 노드까지의 거리를 무한대로 초기화합니다.
    std::vector<bool> visited(n, false);                                       // 방문한 노드를 표시하는 벡터를 초기화합니다.
    distances[startNode] = 0;                                                  // 시작 노드까지의 거리를 0으로 설정합니다.

    // 우선순위 큐를 사용하여 최단 거리를 가진 노드를 우선적으로 처리합니다.
    auto cmp = [&distances](int left, int right)
    { return distances[left] > distances[right]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
    pq.push(startNode); // 시작 노드를 큐에 추가합니다.

    while (!pq.empty())
    {
        int current = pq.top(); // 현재 처리할 노드를 가져옵니다.
        pq.pop();               // 처리할 노드를 큐에서 제거합니다.

        if (visited[current])
            continue; // 이미 방문한 노드는 건너뜁니다.

        visited[current] = true; // 현재 노드를 방문으로 표시합니다.

        // 현재 노드의 모든 이웃 노드를 확인합니다.
        for (int neighbor = 0; neighbor < n; ++neighbor)
        {
            // 현재 노드와 이웃 노드 사이에 경로가 있고, 이웃 노드를 아직 방문하지 않았다면
            if (tableCost[current][neighbor] != std::numeric_limits<double>::infinity() && !visited[neighbor])
            {
                // 현재 노드를 거쳐서 이웃 노드로 가는 새로운 거리를 계산합니다.
                double newDist = distances[current] + tableCost[current][neighbor];
                // 새로운 거리가 기존 거리보다 짧으면
                if (newDist < distances[neighbor])
                {
                    distances[neighbor] = newDist; // 이웃 노드까지의 최단 거리를 갱신합니다.
                    pq.push(neighbor);             // 이웃 노드를 큐에 추가합니다.
                }
            }
        }
    }

    return distances; // 시작 노드에서 다른 모든 노드까지의 최단 거리 벡터를 반환합니다.
}