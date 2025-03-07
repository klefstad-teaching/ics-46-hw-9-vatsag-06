//
// Created by Vatsa Gupta on 3/7/2025.
//


#include "dijkstras.h"

#include <algorithm>
#include <bits/ranges_algo.h>

vector<int> dijkstra_shortest_path(const Graph &G, int source, vector<int> &previous) {
    int numvertices = G.size();
    vector<int> distances(numvertices, INF);
    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    previous[source] = -1;
    while (!minHeap.empty()) {
        int vertex = minHeap.top().second;
        minHeap.pop();
        for (Edge edge : G[vertex]) {
            int v = edge.dst;
            int cost = edge.weight;
            if (distances[vertex] + cost < distances[v]) {
                distances[v] = distances[vertex] + cost;
                previous[v] = vertex;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}


