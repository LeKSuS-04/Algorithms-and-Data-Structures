#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    int n;
    string s;
    vector<int> sa;  // suffix array
    vector<int> rank;
    vector<int> lcp;

    SuffixArray(const string& s) : s(s + '\0') { build(); }

    void counting_sort(int k) {
        vector<int> cnt(256, 0);
        for (int i = 0; i < n; i++) {
            if (i + k < n) {
                ++cnt[rank[i + k]];
            } else {
                ++cnt[0];
            }
        }

        for (int i = 0, sum = 0; i < cnt.size(); i++) {
            int t = cnt[i];
            cnt[i] = sum;
            sum += t;
        }

        vector<int> tmp_sa(n);
        for (const auto& old_sa_i : sa) {
            int j = 0;
            if (old_sa_i + k < n) {
                j = rank[old_sa_i + k];
            }

            tmp_sa[cnt[j]] = old_sa_i;
            cnt[j] += 1;
        }
        swap(sa, tmp_sa);
    }

    void build() {
        n = s.size();

        // build suffix array
        sa.resize(n);
        rank.resize(n);
        iota(sa.begin(), sa.end(), 0);
        for (int i = 0; i < n; i++) {
            rank[i] = s[i];
        }

        for (int k = 1; k < n; k *= 2) {
            counting_sort(k);
            counting_sort(0);

            vector<int> tmp_rank(n);
            int r = 0;
            tmp_rank[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                auto ranks_same = [&](int j) {
                    return rank[sa[i] + j] == rank[sa[i - 1] + j];
                };

                if (ranks_same(0) && ranks_same(k)) {
                    tmp_rank[sa[i]] = r;
                } else {
                    tmp_rank[sa[i]] = ++r;
                }
            }
            swap(rank, tmp_rank);

            if (rank[sa[n - 1]] == n - 1) {
                break;
            }
        }

        // build lcp
        lcp.resize(n);
        for (int i = 0, k = 0; i < n - 2; i++) {
            while (s[i + k] == s[sa[rank[i] - 1] + k]) {
                ++k;
            }
            lcp[rank[i]] = k;
            k = max(k - 1, 0);
        }
    }
};

int main() {
    string s = "abababcbcabab";
    SuffixArray array(s);

    cout << "lcp\tsa\tstring\n";
    for (int i = 0; i < array.sa.size(); i++) {
        cout << array.lcp[i] << '\t' << array.sa[i] << "\t\"" << s.substr(array.sa[i]) << "\"\n";
    }
}
