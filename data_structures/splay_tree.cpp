#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Node {
    Node *l, *r, *p;
    T value;

    Node(const T& v) : l(nullptr), r(nullptr), p(nullptr), value(v) {}
    Node() : value(T()) {}

    void rotate() {
        Node* p = this->p;

        if (this == p->l) {
            Node* a = this->l;
            Node* b = this->r;
            Node* c = p->r;

            if (b != nullptr) {
                b->p = this->p;
            }
            p->l = b;
            this->r = p;
            this->p = p->p;
            p->p = this;
        } else {
            Node* a = p->l;
            Node* b = this->l;
            Node* c = this->r;

            if (b != nullptr) {
                b->p = this->p;
            }
            p->r = b;
            this->l = p;
            this->p = p->p;
            p->p = this;
        }
    }

    void splay() {
        while (p != nullptr) {
            if (p->p == nullptr) {
                rotate();
            } else if ((this == p->l) == (p == p->p->l)) {
                p->rotate();
                rotate();
            } else {
                rotate();
                rotate();
            }
        }
    }

    Node* find(const T& v) {
        Node* x = this;
        while (x != nullptr) {
            if (x->value > v) {
                x = x->l;
            } else if (x->value < v) {
                x = x->r;
            } else {
                splay(x);
                return x;
            }
        }
        return nullptr;
    }

    Node* merge(Node* other) {
        Node* biggest = this;
        while (biggest->r != nullptr) {
            biggest = biggest->r;
        }

        splay(biggest);

        biggest->r = other;
        if (other != nullptr) {
            other->p = biggest;
        }
        return biggest;
    }

    pair<Node*, Node*> split(const T& v) {
        Node* x = this;
        while (true) {
            if (x->value > v && x->l != nullptr) {
                x = x->l;
            } else if (x->value < v && x->r != nullptr) {
                x = x->r;
            } else {
                break;
            }
        }

        x->splay();

        if (x->value < v) {
            Node* y = x->l;
            x->l = nullptr;
            if (y != nullptr) {
                y->p = nullptr;
            }
            return make_pair(y, x);
        }

        Node* y = x->r;
        x->r = nullptr;
        if (y != nullptr) {
            y->p = nullptr;
        }
        return make_pair(x, y);
    }

    Node* add(const T& v) {
        auto [l, r] = split(v);
        Node* root = new Node(v);
        root->l = l;
        if (l != nullptr) {
            l->p = root;
        }

        root->r = r;
        if (r != nullptr) {
            r->p = root;
        }
        return root;
    }

    Node* remove(const T& v) {
        Node* x = find(v);
        if (x != nullptr) {
            Node* a = x->l;
            Node* b = x->r;
            x->l = nullptr;
            x->r = nullptr;
            if (a != nullptr) {
                a->p = nullptr;
            }
            if (b != nullptr) {
                b->p = nullptr;
            }
            return a.merge(b);
        }
        return this;
    }
};

template <typename T>
Node<T>* make_root(T value) {
    return new Node(value);
};
