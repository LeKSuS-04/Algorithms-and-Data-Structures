#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edge {
    int from, to;
    ll cap;
};

struct Graph {
    int n;
    vector<Edge> edges;
    vector<vector<int>> AL;

    Graph(int vertices_count) : n(vertices_count), AL(n) {}

    void add_edge(int u, int v, ll capacity) {
        edges.push_back(Edge{
            .from = u,
            .to = v,
            .cap = capacity,
        });
        edges.push_back(Edge{
            .from = v,
            .to = u,
            .cap = 0LL,
        });
        AL[u].push_back(edges.size() - 2);
        AL[v].push_back(edges.size() - 1);
    }

    ll max_flow(int source, int target) {
        auto bfs = [&](ll min_f, ll max_f) {
            queue<int> q;
            q.push(source);
            vector<int> edge_from_parent(n, -1);
            edge_from_parent[source] = 0;

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (const int i : AL[v]) {
                    const auto& e = edges[i];
                    if (e.cap < min_f || edge_from_parent[e.to] != -1) {
                        continue;
                    }

                    q.push(e.to);
                    edge_from_parent[e.to] = i;
                }
            }

            if (edge_from_parent[target] == -1) {
                return 0LL;
            }

            ll cur = target;
            ll flow = max_f;
            while (cur != source) {
                const auto& e = edges[edge_from_parent[cur]];
                flow = min(flow, e.cap);
                cur = e.from;
            }

            cur = target;
            while (cur != source) {
                int i = edge_from_parent[cur];
                edges[i].cap -= flow;
                edges[i ^ 1].cap += flow;
                cur = edges[i].from;
            }

            return flow;
        };

        ll flow = 0;
        for (ll min_f = 1LL << 30; min_f > 0; min_f >>= 1) {
            while (ll new_flow = bfs(min_f, numeric_limits<ll>::max())) {
                flow += new_flow;
            }
        }
        return flow;
    }
};

int main() {
    istringstream sin(
        "5 7\n"
        "1 3 99\n"
        "1 4 99\n"
        "2 5 4\n"
        "3 5 3\n"
        "3 4 2\n"
        "3 2 3\n"
        "4 2 6\n");

    int n, m;
    sin >> n >> m;

    Graph graph(n);
    while (m--) {
        int u, v, c;
        sin >> u >> v >> c;
        --u, --v;
        graph.add_edge(u, v, c);
    }

    cout << graph.max_flow(0, 4) << endl;
}
