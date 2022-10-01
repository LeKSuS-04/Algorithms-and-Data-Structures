#include <queue>
#include <vector>
using namespace std;

vector<int> in_degree;
vector<vector<int>> AL;
vector<int> sorted;

void kahn_toposort() {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < in_degree.size(); i++) {
        if (in_degree[i] == 0) pq.push(i);
    }

    while (!pq.empty()) {
        int v = pq.top(); pq.pop();
        sorted.push_back(v);

        for (auto&& u : AL[v]) {
            if (--in_degree[u] == 0) pq.push(u);
        }
    }
}