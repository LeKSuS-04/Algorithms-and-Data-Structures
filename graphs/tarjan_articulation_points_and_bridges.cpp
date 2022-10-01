#include <utility>
#include <vector>
using namespace std;

const int UNVISITED = -1;

int dfs_root, root_children, dfs_counter;
vector<vector<int>> AL;
vector<int> dfs_low, dfs_num, dfs_parent;
vector<bool> articulation_points;
vector<pair<int, int>> articulation_bridges;

void find_articulation_points_and_bridges(int u) {
    dfs_num[u] = dfs_low[u] = dfs_counter++;
    for (auto&& v : AL[u]) {
        if (dfs_num[v] == UNVISITED) {
            dfs_parent[v] = u;
            if (u == dfs_root) ++root_children;

            find_articulation_points_and_bridges(v);

            if (dfs_low[v] >= dfs_num[u]) 
                articulation_points[u] = true;
            if (dfs_low[v] > dfs_num[u])
                articulation_bridges.push_back({u, v});
            
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}


int main() {
    int n; // Amount of vertexes

    AL.assign(n, vector<int>()); 
    dfs_low.assign(n, 0);
    dfs_num.assign(n, UNVISITED);
    dfs_parent.assign(n, 0);
    articulation_points.assign(n, false);

    /* INPUT */

    for (int i = 0; i < AL.size(); i++) if(dfs_num[i] == UNVISITED) {
        dfs_root = i;
        dfs_counter = root_children = 0;
        find_articulation_points_and_bridges(dfs_root);
        articulation_points[dfs_root] = (root_children > 1);
    }
}