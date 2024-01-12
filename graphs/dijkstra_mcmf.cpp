#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

const int MAX_V = 1e2 + 15;
const ll INF = numeric_limits<ll>::max() >> 2;
int n, m;

struct Edge {
    int from, to;
    ll cost, cap, flow;

    ll delta() const { return cap - flow; }
};

struct Graph {
    int n;
    vector<vector<int>> AL;
    vector<Edge> edges;

    Graph(int vertices_count) : n(vertices_count), AL(n) {}

    void add_edge(int u, int v, ll cap, ll cost) {
        edges.push_back(Edge{
            .from = u,
            .to = v,
            .cost = cost,
            .cap = cap,
            .flow = 0,
        });
        edges.push_back(Edge{
            .from = v,
            .to = u,
            .cost = -cost,
            .cap = 0,
            .flow = 0,
        });
        AL[u].push_back(edges.size() - 2);
        AL[v].push_back(edges.size() - 1);
    }

    int mcmf(int source, int target) {
        vector<ll> phi(n, 0);
        vector<char> used;

        const auto& ford_bellman = [&] {
            phi.assign(n, INF);
            phi[source] = 0;

            bool changed = true;
            while (changed) {
                changed = false;
                for (const auto& e : edges) {
                    if (e.cap == 0 || phi[e.from] == INF) {
                        continue;
                    }

                    if (phi[e.from] + e.cost < phi[e.to]) {
                        phi[e.to] = phi[e.from] + e.cost;
                        changed = true;
                    }
                }
            }
        };

        const auto& dfs = [&](int v, ll max_f, const auto& self) {
            used[v] = true;

            if (v == target) {
                return max_f == INF ? 0LL : max_f;
            }

            for (auto i : AL[v]) {
                const auto& e = edges[i];

                if (used[e.to] || e.delta() == 0 || e.cost + phi[v] - phi[e.to] != 0) {
                    continue;
                }

                ll flow = self(e.to, min(max_f, e.delta()), self);
                if (flow == 0) {
                    continue;
                }
                edges[i].flow += flow;
                edges[i ^ 1].flow -= flow;
                return flow;
            }

            return 0LL;
        };

        const auto& dijkstra = [&]() {
            priority_queue<ii, vector<ii>, greater<ii>> pq;
            pq.push({0, source});
            vector<ll> distance(n, INF);
            distance[source] = 0;
            vector<int> edge_from_parent(n, -1);

            while (!pq.empty()) {
                auto [w, v] = pq.top();
                pq.pop();

                if (distance[v] != w) {
                    continue;
                }

                for (auto i : AL[v]) {
                    auto& e = edges[i];
                    if (e.delta() == 0) {
                        continue;
                    }

                    ll new_dist = distance[v] + e.cost + phi[v] - phi[e.to];
                    if (new_dist < distance[e.to]) {
                        distance[e.to] = new_dist;
                        edge_from_parent[e.to] = i;
                        pq.push({new_dist, e.to});
                    }
                }
            }

            if (distance[target] == INF) {
                return 0LL;
            }

            for (int i = 0; i < distance.size(); i++) {
                if (distance[i] != INF) {
                    phi[i] += distance[i];
                }
            }

            ll flow = INF;
            int cur = target;
            while (cur != source) {
                const auto& e = edges[edge_from_parent[cur]];
                flow = min(flow, e.delta());
                cur = e.from;
            }

            ll cost = 0;
            cur = target;
            while (cur != source) {
                int i = edge_from_parent[cur];
                edges[i].flow += flow;
                edges[i ^ 1].flow -= flow;
                cost += edges[i].cost * flow;
                cur = edges[i].from;
            }

            return cost;
        };

        ford_bellman();
        ll cost = 0;
        while (auto new_cost = dijkstra()) {
            cost += new_cost;
        }
        return cost;
    }
};

int main() {
    istringstream sin(
        "5 7\n"
        "1 3 99 1\n"
        "1 4 99 1\n"
        "2 5 4 1\n"
        "3 5 3 1\n"
        "3 4 2 1\n"
        "3 2 3 2\n"
        "4 2 6 3\n");

    int n, m;
    sin >> n >> m;

    Graph graph(n);
    while (m--) {
        int u, v, c, w;
        sin >> u >> v >> c >> w;
        --u, --v;
        graph.add_edge(u, v, c, w);
    }

    cout << graph.mcmf(0, 4) << endl;
}
