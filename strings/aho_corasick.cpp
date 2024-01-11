#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    // Task-specific
    const static int ALPHABET_SIZE = 26;
    inline char normalize(char c) { return c - 'a'; }

    inline static const int EMPTY = -1;
    struct Vertex {
        vector<int> to, go;
        int link = EMPTY, parent = EMPTY;
        char c = EMPTY;

        bool terminal = false;

        Vertex() : to(ALPHABET_SIZE, EMPTY), go(ALPHABET_SIZE, EMPTY) {}
    };

    vector<Vertex> vertices;
    int root = 0;

    int new_vertex(int parent, char c) {
        vertices.emplace_back();
        vertices.back().parent = parent;
        vertices.back().c = c;
        return vertices.size() - 1;
    }

    AhoCorasick() { root = new_vertex(EMPTY, 0); }

    void add_string(const string& s) {
        int v = root;
        for (char c : s) {
            c = normalize(c);
            if (vertices[v].to[c] == EMPTY) {
                vertices[v].to[c] = new_vertex(v, c);
            }
            v = vertices[v].to[c];
        }
        vertices[v].terminal = true;
    }

    int link(int vi) {
        Vertex& v = vertices[vi];
        if (v.link == EMPTY) {
            if (vi == root || v.parent == root) {
                v.link = root;
            } else {
                v.link = go(link(v.parent), v.c);
            }
        }
        return v.link;
    }

    int go(int vi, char c) {
        Vertex& v = vertices[vi];
        if (v.go[c] == EMPTY) {
            if (v.to[c] != EMPTY) {
                v.go[c] = v.to[c];
            } else if (vi == root) {
                v.go[c] = root;
            } else {
                v.go[c] = go(link(vi), c);
            }
        }
        return v.go[c];
    }
};

int main() {
    string s = "lolkeklol";
    vector<string> banned = {"lol", "kek"};
    AhoCorasick corasick;

    for (const auto& str : banned) {
        corasick.add_string(str);
    }

    int v = corasick.root;
    int i = 0;
    for (char c : s) {
        ++i;
        v = corasick.go(v, corasick.normalize(c));
        if (corasick.vertices[v].terminal) {
            cout << "banned word ends at i = " << i << endl;
        } else {
            cout << "char at i = " << i << " is good" << endl;
        }
    }
}