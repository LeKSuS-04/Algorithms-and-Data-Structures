#include <bitset>
#include <vector>
using namespace std;

typedef long long ll;

// Relatively fast, ~500ms
const int MAX = 1e7;

vector<int> primes;         // Here will be stored list of primes
bitset<MAX+10> is_prime;    // To check if n is prime, see is_prime[n]

void sieve() {
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    primes.clear();

    for (ll i = 2; i < MAX; i++) if (is_prime[i]) {
        for (ll j = i * i; j < MAX; j += i) is_prime[j] = false;
        primes.push_back(i);
    }
}
