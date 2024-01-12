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
        int iter = 0;
        vector<int> used(n, -1);

        auto dfs = [&](int v, ll min_f, ll max_f, const auto& self) {
            used[v] = iter;

            if (v == target) {
                return max_f;
            }

            for (const auto& i : AL[v]) {
                const auto& e = edges[i];
                if (e.cap < min_f || used[e.to] == iter) {
                    continue;
                }

                ll flow = self(e.to, min_f, min(max_f, e.cap), self);
                if (flow == 0) {
                    continue;
                }

                edges[i].cap -= flow;
                edges[i ^ 1].cap += flow;
                return flow;
            }

            return 0LL;
        };

        ll flow = 0;
        for (ll min_f = 1LL << 30; min_f > 0; min_f >>= 1) {
            while (ll new_flow = dfs(source, min_f, numeric_limits<ll>::max(), dfs)) {
                flow += new_flow;
                ++iter;
            }
            ++iter;
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
