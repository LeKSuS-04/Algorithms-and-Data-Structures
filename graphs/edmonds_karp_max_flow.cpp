#include <bitset>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;
const int MAXSIZE = 110; // Maximum amount of vertexes in graph
                         // (must be known vefore compilation);
int n,                   // Actual amount of vertexes in graph;
    max_flow, f,
    s,                   // Source: vertex to start from;
    t;                   // Destination: vertex to finish in;
vector<vector<int>> AM;  // Adjacency matrix, where;
                         // AM[u][v] = capacity of u -> v edge;
                         // Is 0 if there's empty connection between edges
                         // or no connection at all;
vector<vector<int>> AL;  // Adjacency list
vector<int> p;
bitset<MAXSIZE> visited;


void augment(int v, int bottleneck) {
    if (v == s) { f = bottleneck; }
    else {
        augment(p[v], min(bottleneck, AM[p[v]][v]));
        AM[p[v]][v] -= f;
        AM[v][p[v]] += f;
    }
}

int edmonds_karp_max_flow() {
    max_flow = 0, f = 42;
    while (f != 0) {
        f = 0;

        queue<int> q; q.push(s);
        visited.reset(); visited[s] = true;
        p.assign(n, -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (auto&& v : AL[u]) {
                if (AM[u][v] > 0 && !visited[v]) {
                    visited[v] = true;
                    p[v] = u;
                    q.push(v);
                }
            }
        }

        augment(t, INF);
        max_flow += f;
    }
    return max_flow;
}