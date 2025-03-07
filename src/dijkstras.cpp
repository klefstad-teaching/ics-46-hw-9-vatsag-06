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
    return distances;
}

