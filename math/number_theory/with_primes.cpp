#include <bitset>
#include <math.h>
#include <vector>
using namespace std;

typedef long long ll;

// Sieve of eratosthenes precomputation,
// O(n log log n); ~500ms for n = 1e7
const int MAX = 1e7;
bitset<MAX+10> is_prime;
vector<int> primes;
void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    primes.clear();
    for (ll i = 2; i < MAX; i++) if (is_prime[i]) {
        for (ll j = i * i; j < MAX; j += i) is_prime[j] = 0;
        primes.push_back(i);
    }
}

// All following functions require sieve()
// to be computed before.
// All of them work for n < (lp * lp), where
// lp is the last prime in vector<int> primes.
// So, to use these functions for a number n, 
// you only need sieve of sqrt(n), resulting in
// complexity:
// O(sqrt(n) log log sqrt(n)) precomputation
// + O(sqrt(n)/ln(sqrt(n))) for each n

// Number of prime factors
int num_pf(ll n) {
    int ans = 0;
    ll pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        while (n % pf == 0) { ++ans; n /= pf; }
        pf = primes[++pf_idx];
    }
    if (n != 1) ++ans;
    return ans;
}

// Number of different prime factors
int num_diff_pf(ll n) {
    int ans = 0;
    ll pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        if (n % pf == 0) ++ans;
        while (n % pf == 0) n /= pf;
        pf = primes[++pf_idx];
    }
    if (n != 1) ++ans;
    return ans;
}

// Sum of all prime factors
ll sum_pf(ll n) {
    ll ans = 0, pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        while (n % pf == 0) { ans += pf; n /= pf; }
        pf = primes[++pf_idx];
    }
    if (n != 1) ans += n;
    return ans;
}

// Sum of different prime factors
ll sum_diff_pf(ll n) {
    ll ans, pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        if (n % pf == 0) ans += pf;
        while (n % pf == 0) n /= pf;
        pf = primes[++pf_idx];
    }
    if (n != 1) ans += n;
    return ans;
} 

// Number of prime and composite divisors of n
// (including 1 and n)
ll num_div(ll n) {
    ll ans = 1, pf_idx = 0, pf = primes[pf_idx];
    
    while (pf * pf <= n) {
        int pwr = 0;
        while (n % pf == 0) { ++pwr; n /= pf; }
        ans *= (pwr + 1);
        pf = primes[++pf_idx];
    }
    if (n != 1) ans *= 2;
    return ans;
}

// Sum of all divisors of n
// (including 1 and n)
// Be careful, the answer might not
// fit to long long data type
ll sum_div(ll n) {
    ll ans = 1, pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        ll next_pwr = pf, total = 1;
        while (n % pf == 0) { 
            total += next_pwr;
            next_pwr *= pf;
            n /= pf;
        }
        ans *= total;
        pf = primes[++pf_idx];
    }
    if (n != 1) ans *= (n + 1);
    return ans;
}

// Amount of numbers m from 1 to n
// such that gcd(n, m) = 1
ll eul_phi(ll n) {
    ll ans = n, pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        if (n % pf == 0) ans -= ans/pf;
        while (n % pf == 0) n /= pf;
        pf = primes[++pf_idx];
    }
    if (n != 1) ans -= ans/n;
    return ans;
}
