#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    int l = 0, r = 0;
    Vertex* link = nullptr;
    Vertex* parent = nullptr;
    map<char, Vertex*> to;

    int len() { return r - l; }
};

struct State {
    Vertex* v = nullptr;
    int pos = 0;
};

struct SuffixTree {
    const char PROTECTION = '$';

    string s;
    Vertex* root;
    State current;
    const int INF = numeric_limits<int>::max() >> 2;

    SuffixTree(const string& s) {
        root = new Vertex();
        root->parent = root;
        current = State{.v = root, .pos = 0};

        for (auto c : s) {
            add(c);
        }
        add(PROTECTION);
    }

    State go(State st, int l, int r) {
        while (l < r) {
            if (st.pos == st.v->len()) {
                st = State{
                    .v = st.v->to[s[l]],
                    .pos = 0,
                };
                if (st.v == nullptr) {
                    break;
                }
            } else {
                if (s[st.v->l + st.pos] != s[l]) {
                    return State{.v = nullptr, .pos = 0};
                }

                int d = min(st.v->len() - st.pos, r - l);
                l += d;
                st.pos += d;
            }
        }
        return st;
    }

    Vertex* split(State st) {
        if (st.pos == 0) {
            return st.v->parent;
        }

        if (st.pos == st.v->len()) {
            return st.v;
        }

        Vertex* new_v = new Vertex(Vertex{
            .l = st.v->l,
            .r = st.v->l + st.pos,
            .link = nullptr,
            .parent = st.v->parent,
        });
        st.v->parent->to[s[st.v->l]] = new_v;
        new_v->to[s[st.v->l + st.pos]] = st.v;
        st.v->l += st.pos;
        st.v->parent = new_v;
        return new_v;
    }

    Vertex* get_link(Vertex* v) {
        if (v->link != nullptr) {
            return v->link;
        }

        if (v == root) {
            return v->link = root;
        }

        Vertex* l = get_link(v->parent);
        auto loc = State{.v = l, .pos = l->len()};

        int le = v->l;
        if (v->parent == root) {
            le += 1;
        }
        int ri = v->r;

        auto next = go(loc, le, ri);
        return v->link = split(next);
    }

    void add(char c) {
        s.push_back(c);

        while (true) {
            auto next = go(current, s.size() - 1, s.size());
            if (next.v != nullptr) {
                current = next;
                break;
            }

            Vertex* mid = split(current);
            Vertex* new_v = new Vertex(Vertex{
                .l = (int)s.size() - 1,
                .r = INF,
                .link = nullptr,
                .parent = mid,
            });
            mid->to[c] = new_v;

            if (mid == root) {
                break;
            }

            current.v = get_link(mid);
            current.pos = current.v->len();
        }
    }
};

int main() {
    string s = "abcbabcbab";
    SuffixTree tree(s);
    cout << "kek" << endl;
}