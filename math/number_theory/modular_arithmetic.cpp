const int MOD = 1e9 + 7;

// In C++, module of negative number is a
// negative number; for example:
// -100 % 3 = -1;
// In mathematics, module of a number always
// has to be positive, so 
// -100 % 3 = 2;
// This function forces C++ to act in 
// "math way" and return only positive 
// modules.
long long mod(long long a) { return (a % MOD + MOD) % MOD; }

// In fact, this operations are not worth it 
// to be separated into the whole function,
// so these are made only for demonstration
// purposes
long long  add(long long a, long long b) { return mod(mod(a) + mod(b)); }
long long  sub(long long a, long long b) { return mod(mod(a) - mod(b)); }
long long mult(long long a, long long b) { return mod(mod(a) * mod(b)); } // be careful, might result in overflow

// Rises a to power of b modulo m 
long long pow(long long a, long long b) {
    if (b == 0) return 1;
    else if (b & 1) return mod(a * pow(a, b - 1));
    else return pow(mod(a*a), b/2);
}

// Division is performed by inversing 
// number (Fermat's little theorem)
long long inverse(long long a) { return pow(a, MOD - 2); }
long long divide(long long a, long long b) { return mod(a * inverse(b)); }