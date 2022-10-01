#include <vector>
using namespace std;

const int UNVISITED = 0;
const int VISITED = 1;

vector<int> used;
vector<vector<int>> AL;

void dfs(int v) {
    if (used[v] == VISITED) return;
    used[v] = VISITED;
    for (int i = 0; i < AL[v].size(); i++) {
        dfs(AL[v][i]);
    }
}

int main() {
    int n; // Amount of vertexes
    used.assign(n, UNVISITED);
    AL.assign(n, vector<int>());

    /*
    Input of graph edges 
    */

    int v; // Vertex to start dfs from
    dfs(v);
}