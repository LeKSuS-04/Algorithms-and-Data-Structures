#include <bitset>
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
    is_prime[0] = is_prime[1] = false;
    primes.clear();

    for (ll i = 2; i < MAX; i++) if (is_prime[i]) {
        for (ll j = i * i; j < MAX; j += i) is_prime[j] = false;
        primes.push_back(i);
    }
}

// Requires sieve() to be computed before.
// Works for n < (lp * lp), where lp is
// the last prime in vector<int> primes.
// So, to factorize a number n, you need
// only sieve of sqrt(n), resulting in
// complexity:
// O(sqrt(n) log log sqrt(n)) precomputation
// + O(sqrt(n)/ln(sqrt(n))) for each n
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

// Doesn't require sieve() to be
// precomputed, but runs slower.
// O(sqrt(n))
vector<int> single_prime_factorization(ll n) {
    vector<int> factors;
    ll a = 2;

    while (a * a <= n) {
        while (n % a == 0) { 
            n /= a; 
            factors.push_back(a); 
        }
        ++a;
    }

    if (n != 1) factors.push_back(n);
    return factors;
}
