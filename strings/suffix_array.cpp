#include <iostream>
#include <vector>
using namespace std;

// Suffix Array Data Structure 
// O(n log n) time complexity constrution

// SuffixArray[i] -> index of beginning
// of suffix on i-th place among all other
// suffixes when sorted in lexicographic
// order
// SuffixArray.LCP[i] -> amount of similar
// characters in SuffixArray[i] and 
// SuffixArray[i - 1]

// SuffixArray.size() -> size of Suffix Array
// SuffixArray.base_str() -> string from which
// thi Suffix Array is built. Contains null byte 
// at the end
// SuffixArray.update(string s) -> create new 
// Suffix Array from string s

// OOP style
class SuffixArray {
private:
    const int ASCII_MAX = 260;
    string T;
    int n;
    vector<int> SA, tempSA;
    vector<int> RA, tempRA;
    vector<int> c;

    void counting_sort(int k) {
        c.assign(max(n, ASCII_MAX), 0);
        for (int i = 0; i < n; i++) 
            c[i + k < n ? RA[i + k] : 0]++;

        for (int i = 0, sum = 0; i < c.size(); i++) {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }

        for (int i = 0; i < n; i++)
            tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
        SA = tempSA;
    }

    void construt_SA(string s) {
        T = s + char(0);
        n = T.size();

        SA.resize(n), tempSA.resize(n);
        RA.resize(n), tempRA.resize(n);
        for (int i = 0; i < n; i++) SA[i] = i, RA[i] = T[i];
        for (int k = 1, r = 0; k < n; k <<= 1) {
            counting_sort(k);
            counting_sort(0);

            tempRA[SA[0]] = r = 0;
            for (int i = 1; i < n; i++)
                tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
            RA = tempRA;
            if (RA[SA[n - 1]] == n - 1) break;
        }

        LCP.resize(n);
        for (int i = 0, k = 0; i < n - 2; i++) {
            while (T[i + k] == T[SA[RA[i] - 1] + k]) ++k;
            LCP[RA[i]] = k;
            k = max(k - 1, 0);
        }
    }
public:
    vector<int> LCP;
    SuffixArray(string s = "")  { construt_SA(s); }

    void update(string s) { construt_SA(s); }
    int operator[](int idx) { return SA[idx]; }
    int size() { return n; }
};


int main() {    
    string s;
    getline(cin, s);
    SuffixArray SA(s);

    for (int i = 0; i < SA.size(); i++) 
        cout << SA.LCP[i] << " " << SA[i] << "\t\"" << s.substr(SA[i]) << "\"\n";
}
