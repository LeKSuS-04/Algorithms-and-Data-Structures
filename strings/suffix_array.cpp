#include <iostream>
#include <vector>
using namespace std;

// Still under work

const int ASCII_MAX = 260;
string T;
int n;
vector<int> RA, tempRA;
vector<int> SA, tempSA;
vector<int> c;

void counting_sort(int k) {
    int i, sum, maxi = max(ASCII_MAX, n);
    c.assign(maxi, 0);

    for (i = 0; i < n; i++) c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    SA = tempSA;
}

void construct_SA() {
    RA.resize(n), tempRA.resize(n);
    SA.resize(n), tempSA.resize(n);

    int i, k, r;
    for (i = 0; i < n; i++) SA[i] = i, RA[i] = T[i];
    for (k = 1; k < n; k <<= 1) {
        counting_sort(k);
        counting_sort(0);

        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++) 
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        RA = tempRA;
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

int main() {
    getline(cin, T); T += char(0);
    n = T.size();
    construct_SA();

    for (int i = 0; i < n; i++) 
        cout << SA[i] << "\t\"" << T.substr(SA[i]) << "\"\n";
}
