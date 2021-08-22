#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

vector<vector<int>> grid; // Assume this is some grid to explore

const int DIRCOUNT = 8;
int dr[] = { 1, 1, 1, 0, 0,-1,-1,-1};
int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};
// Standart floodfill (dfs)
void floodfill(int from, int to, int r, int c) {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[r].size()) return;
    if (grid[r][c] != from) return;

    grid[r][c] = to;
    for (int i = 0; i < DIRCOUNT; i++) {
        floodfill(from, to, r + dr[i], c + dc[i]);
    }
}

// Standart with amount of cells filled (still dfs)
int floodfill_count(int from, int to, int r, int c) {
    if (r < 0 || r >= grid.size() || c < 0 || c >= grid[r].size()) return 0;
    if (grid[r][c] != from) return 0;

    grid[r][c] = to;
    int ans = 1;
    for (int i = 0; i < DIRCOUNT; i++) {
        ans += floodfill_count(from, to, r + dr[i], c + dc[i]);
    }
    return ans;
}

// Bfs implementation to avoid stack overflow with recursion
int bfs_floodfill_count(int from, int to, int r, int c) {
    queue<pair<int, int>> q; q.push({r, c});

    int ans = 0;
    pair<int, int> v;
    while (!q.empty()) {
        v = q.front(); q.pop();
        if (v.first < 0 || v.first >= grid.size() ||
            v.second < 0 || v.second >= grid[v.first].size()) continue;
        if (grid[v.first][v.second] != from) continue;

        ++ans;
        for (int i = 0; i < DIRCOUNT; i++) {
            q.push({v.first + dr[i], v.second + dc[i]});
        }
    }
    return ans;
}