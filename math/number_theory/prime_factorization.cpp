#include <bitset>
#include <vector>
using namespace std;

typedef long long ll;

// Sieve of eratosthenes precomputation,
// O(n log log n)
const int MAX = 1e7;
bitset<MAX+10> is_prime;
vector<int> primes;
void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    primes.clear();

    for (ll i = 2; i < MAX; i++) if (is_prime[i]) {
        for (ll j = i * i; j < MAX; j += i) is_prime[j] = false;
        primes.push_back(i);
    }
}

// Requires sieve() to be computed before
// Works for n <= (9999991 * 9999991) = 99999820000081
// ~ O(sqrt(n)/ln(sqrt(n)))
vector<int> prime_factorization(ll n) {
    vector<int> factors;
    ll pf_idx = 0, pf = primes[pf_idx];

    while (pf * pf <= n) {
        while (n % pf == 0) {
            n /= pf;
            factors.push_back(pf);
        }
        pf = primes[++pf_idx];
    }

    if (n != 1) factors.push_back(n);
    return factors;
}
