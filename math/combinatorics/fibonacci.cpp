#include <stdio.h>
#include <math.h>
using namespace std;

const int SIZE = 100;

// Works correctly up to n = 75 with O(1) time/space complexity
const double sqrt5 = sqrt(5);
const double phi = (1 + sqrt5)/2;
long long Binet(int n) {
    return (pow(phi, n) - pow(-phi, -n))/sqrt5 + 0.5;
}

// Works correctly for any n with O(1) time complexity
// and O(n) precomputations and space complexity.
// Note that Fibonacci numbers from n = 93
// don't fit into long long data type.
long long memo[SIZE];
void dp() {
    memo[1] = memo[2] = 1;
    for (int i = 3; i < SIZE; i++) 
        memo[i] = memo[i - 1] + memo[i - 2];
}

int main() {
    dp();
    for (int n = 1; n < SIZE; n++) 
        printf("n = %3d; binet: %20lld, dp: %20lld\n", n, Binet(n), memo[n]);
}