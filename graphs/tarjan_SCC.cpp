#include <vector>
using namespace std;

const int UNVISITED = -1;

int dfs_count = 0, SCC_amount = 0;
vector<vector<int>> AL, SCCs;
vector<int> dfs_low, dfs_num, dfs_stack;
vector<bool> dfs_on_stack;

void tarjan_SCC(int u) {
    dfs_low[u] = dfs_num[u] = dfs_count++;
    dfs_stack.push_back(u);
    dfs_on_stack[u] = true;

    for (auto&& v : AL[u]) {
        if (dfs_num[v] == UNVISITED) tarjan_SCC(v);
        if (dfs_on_stack[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_num[u] == dfs_low[u]) {
        SCCs.push_back(vector<int>());
        while (true) {
            int v = dfs_stack.back();
            dfs_stack.pop_back(), dfs_on_stack[v] = false;
            SCCs.back().push_back(v);
            if (u == v) break;
        }
        SCC_amount++;
    }
}

int main() {
    int n;  // Amount of vertexes

    AL.assign(n, vector<int>());
    dfs_low.assign(n, 0);
    dfs_num.assign(n, UNVISITED);
    dfs_on_stack.assign(n, false);

    /* INPUT */

    for (int i = 0; i < AL.size(); i++)
        if (dfs_num[i] == UNVISITED) tarjan_SCC(i);
}