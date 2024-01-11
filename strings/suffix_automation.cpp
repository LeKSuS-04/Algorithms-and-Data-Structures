#include <bits/stdc++.h>
using namespace std;

struct Vertex {
    map<char, Vertex*> to;
    Vertex* link = nullptr;
    int len = 0;
    bool terminal = false;

    Vertex* clone() {
        Vertex* copy = new Vertex();
        copy->to = to;
        copy->link = link;
        copy->len = len;
        return copy;
    }
};

struct Automation {
    Automation(const string& s) {
        root = new Vertex();
        last = root;
        for (char c : s) {
            add(c);
        }

        while (last != nullptr) {
            last->terminal = true;
            last = last->link;
        }
    }

    void add(char c) {
        Vertex* current = new Vertex();
        current->len = last->len + 1;

        Vertex* p = last;
        while (p != nullptr && p->to[c] == nullptr) {
            p->to[c] = current;
            p = p->link;
        }

        if (p != nullptr) {
            Vertex* q = p->to[c];
            if (p->len + 1 == q->len) {
                current->link = q;
            } else {
                Vertex* new_v = q->clone();
                new_v->len = p->len + 1;
                q->link = current->link = new_v;
                while (p != nullptr && p->to[c] == q) {
                    p->to[c] = new_v;
                    p = p->link;
                }
            }
        } else {
            current->link = root;
        }

        last = current;
    }

    Vertex* root;
    Vertex* last;
};

int main() {
    string s = "abcb";
    Automation a(s);
}
