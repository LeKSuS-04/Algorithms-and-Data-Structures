#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int mst_cost;
vector<pair<int, int>> MST;

int n; // Amount of vertexes
vector<pair<int, pair<int, int>>> EL; // Edge List: {weight, {from, to}}

class UFDS {
private:
    int num_of_sets;
    vector<int> p, rank;
public:
    UFDS(int n) {
        num_of_sets = n;
        rank.assign(n, 0);
        p.assign(n, 0);
        for (int i = 0; i < p.size(); i++) p[i] = i;
    }

    int find_set(int i) { return (p[i] == i ? i : (p[i] = find_set(p[i]))); }
    bool union_set(int i, int j) {
        int x = find_set(i), y = find_set(j);
        if (x == y) return false;

        if (rank[x] > rank[y]) swap(x, y);
        if (rank[x] == rank[y]) ++rank[y];
        p[x] = y;
        --num_of_sets;

        return true;
    }
    int sets() { return num_of_sets; }
};

void kruskal_mst() {
    mst_cost = 0;
    MST.clear();

    sort(EL.begin(), EL.end());

    UFDS ufds(n);
    for (int i = 0; i < EL.size() && ufds.sets() > 1; i++) {
        auto e = EL[i];
        if (ufds.union_set(e.second.first, e.second.second)) {
            mst_cost += e.first;
            MST.push_back({e.second.first, e.second.second});
        }
    }
}
