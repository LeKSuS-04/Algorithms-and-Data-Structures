#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Func, typename DefaultValue>
class PersistentSegmentTree {
   private:
    struct Node {
        PersistentSegmentTree& pst;
        Node *l, *r, *p;
        int lb, rb;
        T val;

        Node(PersistentSegmentTree& pst, Node* p, int lb, int rb) : pst(pst), p(p), lb(lb), rb(rb) {
            if (lb == rb) {
                val = pst.default_value(lb);
            } else {
                int m = (lb + rb) / 2;
                l = new Node(pst, this, lb, m);
                r = new Node(pst, this, m + 1, rb);
                val = pst.func(l->val, r->val);
            }
        }

        void copy() {
            if (l != nullptr) {
                l = new Node(*l);
                r = new Node(*r);
            }
        }

        void add(int i, T delta) {
            copy();
            val += delta;
            if (l == nullptr) {
                return;
            }

            if (i <= l->rb) {
                l->add(i, delta);
            } else {
                r->add(i, delta);
            }
        }

        T query(int lq, int rq) {
            if (lq > rq) {
                return T();
            }
            if (lq <= lb && rb <= rq) {
                return val;
            }

            int m = (lq + rq) / 2;
            return pst.func(l->query(lq, m), r->query(m + 1, rq));
        }
    };

    Func func;
    DefaultValue default_value;
    vector<Node*> roots;

    Node* get_version_root(int version) {
        if (version == -1) {
            version = roots.size() - 1;
        }
        return new Node(*roots[version]);
    }

   public:
    PersistentSegmentTree(int size, Func f, DefaultValue d) : func(f), default_value(d) {
        Node root(*this, nullptr, 0, size - 1);
        roots.push_back(new Node(root));
    }

    int add(int i, T delta, int version = -1) {
        Node* new_root = get_version_root(version);
        new_root->add(i, delta);
        roots.push_back(new_root);
        return roots.size() - 1;
    }

    T query(int lq, int rq, int version = -1) {
        Node* root = get_version_root(version);
        return root->query(lq, rq);
    }
};

int main() {
    PersistentSegmentTree<int, function<int(int, int)>, function<int(int)>> tree(
        5,
        [](int a, int b) { return a + b; },
        [](int i) { return i; }
    );

    cout << tree.query(0, 4) << endl;

    tree.add(0, 10);
    cout << tree.query(0, 4, 0) << endl;
    cout << tree.query(0, 4, 1) << endl;

    tree.add(0, 5, 0);
    cout << tree.query(0, 4, 0) << endl;
    cout << tree.query(0, 4, 1) << endl;
    cout << tree.query(0, 4, 2) << endl;
}
