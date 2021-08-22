#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int UNVISITED = 0;
const int VISITED = 1;

vector<int> used;
vector<vector<int>> AL;

void bfs(int u) {
    queue<int> q; q.push(u);

    int v;
    while (!q.empty()) {
        v = q.front(); q.pop();
        used[v] = VISITED;
        
        for (int i = 0; i < AL[v].size(); i++) {
            if (used[AL[v][i]] == UNVISITED) q.push(AL[v][i]);
        }
    }
}

int main() {
    int n; // Amount of vertexes
    used.assign(n, UNVISITED);
    AL.assign(n, vector<int>());

    /*
    Input of graph edges 
    */

    int v; // Vertex to start bfs from
    bfs(v);
}