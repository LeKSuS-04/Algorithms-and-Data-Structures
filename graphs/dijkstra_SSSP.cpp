#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> ii;

const int INF = 1e9;

vector<vector<ii>> AL; // AL[u] = {v, w} => path from u to v weigths w
vector<int> dist;

void dijkstra(int from) {
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({0, from});
    dist.assign(AL.size(), INF);
    dist[from] = 0;

    while (!pq.empty()) {
        ii u = pq.top();
        pq.pop();

        if (u.first == dist[u.second]) {
            for (auto&& v : AL[u.second]) {
                if (u.first + v.second < dist[v.first]) {
                    dist[v.first] = u.first + v.second;
                    pq.push({dist[v.first], v.first});
                }
            }
        }
    }
}