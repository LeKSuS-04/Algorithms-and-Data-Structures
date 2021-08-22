#include <vector>
using namespace std;

class UFDS {
private:
    int n;
    vector<int> p, rank, s;
public:
    UFDS(int size) {
        p.assign(size, 0); for (int i = 0; i < size; i++) p[i] = i;
        rank.assign(size, 0);
        s.assign(size, 1);
        n = size;
    }

    int find_set(int i) { return (p[i] == i ? i : (p[i] = find_set(i))); }
    bool is_same_set(int i, int j) {  return find_set(i) == find_set(j); }
    void union_sets(int i, int j) {
        if (!is_same_set(i, j)) {
            int x = find_set(i), y = find_set(j);
            if (rank[x] > rank[y]) swap(x, y);
            if (rank[x] == rank[y]) ++rank[y];
            p[x] = y;
            s[y] += s[x];
            --n;
        }
    }
    int set_size(int i) { return s[find_set(i)]; }
    int count() { return n; }
};