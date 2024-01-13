#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
vector<int> match;
vector<char> used;

bool dfs(int v) {
    if (used[v]) {
        return false;
    }

    used[v] = true;

    for (int u : AL[v]) {
        if (match[u] == -1 || dfs(match[u])) {
            match[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    istringstream sin(
        "8 5\n"
        "1 4\n"
        "1 5\n"
        "1 6\n"
        "2 5\n"
        "3 5\n");

    int n, m;
    sin >> n >> m;

    AL.resize(n);
    while (m--) {
        int u, v;
        sin >> u >> v;
        --u, --v;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    match.assign(n, -1);

    int count = 0;
    for (int i = 0; i < n; i++) {
        used.assign(n, false);
        if (dfs(i)) {
            count += 1;
        }
    }

    cout << count << endl;
}
