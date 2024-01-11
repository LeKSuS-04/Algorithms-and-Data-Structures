#include <bits/stdc++.h>
using namespace std;

/*
0 1 2 3 4 5 6
a a b a a a b
0 1 0 2 3 1 0
*/

vector<int> build_prefix(const string& s) {
    vector<int> z(s.size(), 0);
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < s.size() && s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }

        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    return z;
}

int main() {
    string s = "aabaaab";
    auto z = build_prefix(s);
    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << ' ' << z[i] << endl;
    }
}