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
        vector<int> distance, next_edge;

        auto bfs = [&](ll min_f) {
            queue<int> q;
            q.push(source);
            distance.assign(n, -1);
            distance[source] = 0;

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (const int i : AL[v]) {
                    const auto& e = edges[i];
                    if (e.cap < min_f || distance[e.to] != -1) {
                        continue;
                    }

                    q.push(e.to);
                    distance[e.to] = distance[v] + 1;
                }
            }
        };

        auto dfs = [&](int v, ll min_f, ll max_f, const auto& self) {
            if (v == target) {
                return max_f;
            }

            ll flow = 0;

            for (int& i = next_edge[v]; i < AL[v].size(); i++) {
                int j = AL[v][i];

                const auto& e = edges[j];
                if (e.cap < min_f || distance[e.to] <= distance[v]) {
                    continue;
                }

                int new_flow = self(e.to, min_f, min(max_f - flow, e.cap), self);
                if (new_flow == 0) {
                    continue;
                }

                edges[j].cap -= new_flow;
                edges[j ^ 1].cap += new_flow;
                flow += new_flow;
            }

            return flow;
        };

        ll flow = 0, new_flow = 0;
        for (ll min_f = 1LL << 30; min_f > 0; min_f >>= 1) {
            do {
                bfs(min_f);
                next_edge.assign(n, 0);
                new_flow = dfs(source, min_f, numeric_limits<ll>::max(), dfs);
                flow += new_flow;
            } while (new_flow > 0);
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
