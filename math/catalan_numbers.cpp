typedef long long ll;

// Maximum value, such so that for every
// 0 <= n <= 34, cat[n] fits into long long
// data type
const int MAX = 34;
ll cat[MAX];

// DP, O(n)
void precompute() {
    cat[0] = 1;
    for (int n = 1; n < MAX; n++) {
        cat[n] = cat[n - 1] * (4*n - 2) / (n + 1);
    }
}