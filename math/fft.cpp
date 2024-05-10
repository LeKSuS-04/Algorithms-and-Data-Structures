#include <bits/stdc++.h>
using namespace std;

constexpr double pi = 3.141592653589793;
typedef complex<double> domain;

void fft(vector<domain>& p, domain wn) {
    int n = p.size();
    if (n == 1) {
        return;
    }

    vector<domain> even(n/2), odd(n/2);
    for (int i = 0; i < n/2; i++) {
        even[i] = p[2*i];
        odd[i] = p[2*i + 1];
    }

    fft(even, wn * wn);
    fft(odd, wn * wn);

    domain w = 1;
    for (int i = 0; i < n/2; i++) {
        p[i] = even[i] + w * odd[i];
        p[i + n/2] = even[i] - w * odd[i];
        w *= wn;
    }
}

bool is_power_2(int value) {
    return (value & (value - 1)) == 0;
}

vector<domain> evaluate(const vector<int>& coefs) {
    vector<domain> points = {coefs.begin(), coefs.end()};
    fft(points, polar(1.0, 2 * pi / points.size()));
    return points;
}

vector<int> interpolate(vector<domain> points) {
    int n = points.size();
    fft(points, polar(1.0, -2 * pi / points.size()));
    vector<int> coefs;
    for (const auto& val : points) {
        coefs.push_back(round(real(val) / n));
    }
    return coefs;
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    while (a.size() < n) a.push_back(0);
    while (b.size() < n) b.push_back(0);

    auto points_a = evaluate(a);
    auto points_b = evaluate(b);
    vector<domain> points_c(a.size());

    for (int i = 0; i < points_c.size(); i++) {
        points_c[i] = points_a[i] * points_b[i];
    }

    auto c = interpolate(points_c);
    while (c.size() > 1 && c.back() == 0) c.pop_back();
    return c;
}

int main() {
    vector<int> a = {1, -3, 2};
    vector<int> b = {2, 5, 1};
    vector<int> c = multiply(a, b);

    for (const auto& ci : c) {
        cout << ci << ' ';
    }
    cout << endl;
}