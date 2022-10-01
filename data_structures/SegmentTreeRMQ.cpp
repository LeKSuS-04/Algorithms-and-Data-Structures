#include <vector>
using namespace std;

// Implented only single-element updates;
// TODO: Updates on range

class SegmentTree {
private:
    int n;
    vector<int> A, st;

    int l(int p) { return (p << 1); }
    int r(int p) { return (p << 1) + 1; }

    void build(int p, int L, int R) {
        if (L == R) st[p] = A[L];
        else {
            int m = (L + R)/2;
            build(l(p),     L, m);
            build(r(p), m + 1, R);
            st[p] = min(st[l(p)], st[r(p)]);
        }
    }

    int rmq(int p, int L, int R, int i, int j) {
        if (i > j) return -1;
        if (i >= L && j <= R) return st[p];

        int m = (L + R) / 2;
        int lsubtree = rmq(l(p),     L, m,             i, min(j, m));
        int rsubtree = rmq(r(p), m + 1, R, max(i, m + 1),         j);

        if (lsubtree == -1) return rsubtree;
        if (rsubtree == -1) return lsubtree;

        return min(lsubtree, rsubtree);
    }

    void update(int p, int L, int R, int i, int val) {
        if (i < L || i > R) return;
        if (L == R) {
            A[L] = val;
            st[p] = A[L];
        } else {
            int m = (L + R) / 2;
            update(l(p),     L, m, i, val);
            update(r(p), m + 1, R, i, val);
        }
    }
public:
    SegmentTree(int size) : n(size), st(4 * size) {}
    SegmentTree(vector<int> v) {
        A = v;
        build(1, 0, n - 1);
    }

    void update(int i, int val) { update(1, 0, n - 1, i, val); }
    int rmq (int i, int j) { return rmq(1, 0, n - 1, i, j); }
};