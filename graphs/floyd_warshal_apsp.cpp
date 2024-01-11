#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

int n;                   // Amount of vertexes;
vector<vector<int>> AM;  // Adjacency matrix, where
                         // AM[u][v] by default is the cost
                         // of traveling from u to v;
                         // or INF if no direct way from u to v exists;
vector<vector<int>> p;   // p[u][v] = u by default if there is
                         // a direct way from u to v
                         // or INF if no direct way from u to v exists;

void floyd_warshal_APSP() {
    for (int k = 0; k < n; k++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (AM[u][k] + AM[k][v] < AM[u][v]) {
                    AM[u][v] = min(AM[u][v], AM[u][k] + AM[k][v]);
                    p[u][v] = p[k][v];
                }
}

bool path_exists(int u, int v) { return (AM[u][v] != INF); }

// if path_exists(u, v) == false, this will try to
// access p[u][INF], and therefore error will occur;
// So if there might be no way from u to v, check if path_exists(u, v)
// before calling print_path(u, v);
void print_path(int u, int v) {
    if (u != v) print_path(u, p[u][v]);
    cout << " " << v;
}