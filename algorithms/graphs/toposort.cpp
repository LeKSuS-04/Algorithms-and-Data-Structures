#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int UNVISITED = 0;
const int VISITED = 1;

vector<int> used;
vector<vector<int>> AL;
vector<int> sorted;

void toposort(int v) {
    if (used[v] == VISITED) return;
    used[v] = VISITED;

    for (int i = 0; i < AL[v].size(); i++) {
        toposort(AL[v][i]);
    }

    sorted.push_back(v);
}

int main() {
    int n; // Amount of vertexes
    used.assign(n, UNVISITED);
    AL.assign(n, vector<int>());
    sorted.clear(); 

    /*
    Input of graph edges 
    */

    for (int v = 0; v < n; v++) {
        toposort(v);
    }
    reverse(sorted.begin(), sorted.end());  // Note that values after toposort
                                            // will be in reverse order
}