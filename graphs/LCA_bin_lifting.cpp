#include <bits/stdc++.h>
using namespace std;

int logn;
vector<vector<int>> AL, up;
vector<int> tin, tout;
int timer;

void build_lca(int u, int p) {
    tin[u] = timer++;
    up[u][0] = p;
    for (int i = 1; i <= logn; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : AL[u]) {
        if (v != p) {
            build_lca(v, u);
        }
    }
    tout[u] = timer++;
}

bool is_anc(int p, int c) { return tin[p] <= tin[c] && tout[p] >= tout[c]; }

int lca(int u, int v) {
    if (is_anc(u, v)) return u;
    if (is_anc(v, u)) return v;
    for (int i = logn; i >= 0; i--) {
        if (!is_anc(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}