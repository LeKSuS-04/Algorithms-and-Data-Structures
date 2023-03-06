#include <bits/stdc++.h>
using namespace std;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);

class Treap {
   private:
    struct Node {
        int key, p;
        shared_ptr<Node> l = nullptr, r = nullptr;
        Node(int key) : key(key), p(rng()) {}
    };
    using NodePtr = shared_ptr<Node>;
    using NodePair = pair<NodePtr, NodePtr>;

    NodePtr root = nullptr;

    static NodePtr merge(NodePtr t1, NodePtr t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;
        if (t1->p > t2->p) {
            t1->r = merge(t1->r, t2);
            return t1;
        } else {
            t2->l = merge(t1, t2->l);
            return t2;
        }
    }

    static NodePair split(NodePtr t, int key) {
        if (t == nullptr) return {nullptr, nullptr};
        if (t->key <= key) {
            auto [fst, snd] = split(t->r, key);
            t->r = fst;
            return {t, snd};
        } else {
            auto [fst, snd] = split(t->l, key);
            t->l = snd;
            return {fst, t};
        }
    }

   public:
    bool contains(int key) {
        auto [less, greater] = split(root, key);
        auto [less, equal] = split(less, key - 1);
        bool result = (equal == nullptr);
        root = merge(merge(less, equal), greater);
        return result;
    }

    void insert(int key) {
        NodePtr new_node = make_shared<Node>(key);
        auto [l, r] = split(root, key);
        root = merge(l, merge(new_node, r));
    }

    void erase(int key) {
        auto [less, greater] = split(root, key);
        auto [less, equal] = split(less, key - 1);
        root = merge(less, greater);
    }
};