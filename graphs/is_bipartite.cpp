#include <vector>
#include <queue>
using namespace std;

const int UNVISITED = 0;
const int A = 1;
const int B = 2;

vector<int> color;
vector<vector<int>> AL;

bool is_bipartite(int v) {
    color.assign(AL.size(), UNVISITED);

    queue<int> q;
    q.push(v); color[v] = A;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto&& v : AL[u]) {
            if (color[v] == UNVISITED) {
                color[u] = (color[v] == A ? B : A);
                q.push(u);
            } else if (color[u] == color[v]) return false;
        }
    }
    return true;
}