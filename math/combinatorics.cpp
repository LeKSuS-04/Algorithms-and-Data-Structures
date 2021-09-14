// from modular_arithmetic.cpp
const int MOD = 1e9 + 7;
long long mod(long long a) { return (a % MOD + MOD) % MOD; }
long long pow(long long a, long long b) {
    if (b == 0) return 1;
    else if (b & 1) return mod(a * pow(a, b - 1));
    else return pow(mod(a*a), b/2);
}
long long inverse(long long a) { return pow(a, MOD - 2); }


const int MAX_N = 1e5 + 10;

// Factorial precomputing; O(n) time/space
// complexity.
// Inversions of n! are also stored to compute
// C(n, k) with O(1), not O(log MOD) due to the 
// fact that division n!/(k! * (n - k)!) needs
// to raise a to power of MOD - 2
long long fact[MAX_N], inv_fact[MAX_N];
void precompute_fact() {
    fact[0] = 1;
    for (int i = 1; i < MAX_N; i++)
        fact[i] = mod(fact[i - 1] * i);

    inv_fact[MAX_N - 1] = inverse(fact[MAX_N - 1]);
    for (int i = MAX_N - 2; i >= 0; i--) 
        inv_fact[i] = mod(inv_fact[i + 1] * (i + 1));
}

// Combinations - O(1). Requires factorials 
// to be precomputed with O(n) complexity.
long long C(long long n, long long k) {
    if (n < k) return 0;
    else return mod(mod(fact[n] * inv_fact[k]) * inv_fact[n - k]);
}