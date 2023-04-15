#include <bits/stdc++.h>
using namespace std;

class Zmod {
    static const int MOD = 59;
    using ll = long long;

   private:
    ll val;

    inline ll mod(ll n) const { return (MOD + n % MOD) % MOD; }

   public:
    Zmod(ll n = 0) : val(mod(n)) {}

    Zmod operator-() const { return mod(-val); }
    Zmod operator+() const { return mod(-val); }

    Zmod operator+(const Zmod& other) const { return mod(val + other.val); }
    Zmod operator-(const Zmod& other) const { return mod(val - other.val); }
    Zmod operator*(const Zmod& other) const { return mod(val * other.val); }

    friend Zmod pow(Zmod n, ll p) {
        if (p == 0) return 1;
        if (p % 2 == 0) return pow(n * n, p / 2);
        return n * pow(n, p - 1);
    }
    friend Zmod pow(Zmod n, Zmod p) { return pow(n, p.val); }

    Zmod inverse() const { return pow(*this, MOD - 2); }
    Zmod operator/(const Zmod& other) const { return operator*(other.inverse()); }

    friend std::istream& operator>>(std::istream& in, Zmod& n) {
        ll val;
        in >> val;
        n = Zmod(val);
        return in;
    }

    friend std::ostream& operator<<(std::ostream& out, const Zmod& n) {
        out << n.val;
        return out;
    }
};

int main() {
    Zmod a, b;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "-a = -" << a << " = " << -a << endl;
    cout << "a + b = " << a << " + " << b << " = " << a + b << endl;
    cout << "a - b = " << a << " - " << b << " = " << a - b << endl;
    cout << "a * b = " << a << " * " << b << " = " << a * b << endl;
    cout << "a / b = " << a << " / " << b << " = " << a / b << endl;
    cout << "pow(a, b) = " << a << "^" << b << " = " << pow(a, b) << endl;
}