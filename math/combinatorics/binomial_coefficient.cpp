#include <string.h>

typedef long long ll;

// Maximum value, such so that for every
// 0 <= k <= n <= 67, C[n][k] fits into
// long long data type
const int MAX = 67;
ll C[MAX][MAX];

// DP, O(n^2)
void precompute() {
    memset(C, 0, sizeof C);
    C[0][0] = 1;
    for (int i = 1; i < MAX; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
}