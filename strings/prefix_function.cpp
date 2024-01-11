#include <bits/stdc++.h>
using namespace std;

/*
0 1 2 3 4 5 6
a a b a a a b
0 1 0 1 2 2 3
*/

vector<int> build_prefix(const string& s) {
    vector<int> p(s.size(), 0);
    for (int i = 1; i < s.size(); i++) {
        int j = p[i - 1];
        while (j != 0 && s[i] != s[j]) {
            j = p[j - 1];
        }

        if (s[i] == s[j]) {
            p[i] = j + 1;
        }
    }
    return p;
}

int main() {
    string s = "aabaaab";
    auto prefix = build_prefix(s);
    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << ' ' << prefix[i] << endl;
    }
}
