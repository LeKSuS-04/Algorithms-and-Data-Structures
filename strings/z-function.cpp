#include <string>
#include <vector>
using namespace std;

string s;
vector<int> z;

void create_z() {
    z.assign(s.size(), 0);

    int l = 0, r = 0;
    for (int i = 1; i < s.size(); i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (z[i] + i < s.size() && s[z[i] + i] == s[z[i]]) ++z[i];

        if (z[i] + i - 1 > r) l = i, r = z[i] + i - 1;
    }
}